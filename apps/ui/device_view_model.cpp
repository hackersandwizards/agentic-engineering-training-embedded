#include "device_view_model.h"

#include "protocol/c1link.h"

#include <QByteArray>

#include <cmath>
#include <limits>

namespace {

QString fault_name(culina::c1link::FaultCode fault) {
    using culina::c1link::FaultCode;
    switch (fault) {
    case FaultCode::None:
        return {};
    case FaultCode::Overtemp:
        return QStringLiteral("Over-temperature");
    case FaultCode::MotorStall:
        return QStringLiteral("Motor stalled");
    case FaultCode::SensorFailure:
        return QStringLiteral("Temperature sensor failure");
    case FaultCode::LinkLost:
        return QStringLiteral("MCU link lost");
    }
    return QStringLiteral("Unknown fault");
}

} // namespace

DeviceViewModel::DeviceViewModel(culina::sim::SocketTransport uart, const QString& control_socket,
                                 const QString& recipe_dir, QObject* parent)
    : QObject(parent), uart_(std::move(uart)), runtime_(&uart_, &clock_, &watchdog_) {
    if (runtime_.recipes().load_directory(recipe_dir.toUtf8().constData()) == culina::Status::Ok) {
        for (std::size_t i = 0; i < runtime_.recipes().count(); ++i) {
            recipe_names_.append(QString::fromUtf8(runtime_.recipes().at(i)->name));
        }
    }

    connect(&control_, &QLocalSocket::readyRead, this, &DeviceViewModel::readSimulatorResponse);
    connect(&control_, &QLocalSocket::stateChanged, this, &DeviceViewModel::stateChanged);
    control_.connectToServer(control_socket);

    timer_.setTimerType(Qt::PreciseTimer);
    timer_.setInterval(1);
    connect(&timer_, &QTimer::timeout, this, &DeviceViewModel::tick);
    timer_.start();
    refresh();
}

bool DeviceViewModel::controlConnected() const {
    return control_.state() == QLocalSocket::ConnectedState;
}

QString DeviceViewModel::sessionState() const {
    return QString::fromLatin1(culina::app::session_state_name(runtime_.controller().state()));
}

QString DeviceViewModel::programName() const {
    return QString::fromUtf8(runtime_.controller().program_name());
}

QString DeviceViewModel::programStatus() const {
    return QString::fromUtf8(runtime_.controller().program_status());
}

double DeviceViewModel::temperature() const {
    return static_cast<double>(runtime_.controller().display_avg_temp_c());
}

int DeviceViewModel::weight() const {
    return runtime_.telemetry().latest().grams;
}

int DeviceViewModel::rpm() const {
    return runtime_.telemetry().latest().rpm;
}

QString DeviceViewModel::lidState() const {
    const std::uint8_t flags = runtime_.telemetry().latest().flags;
    if ((flags & culina::c1link::kFlagLidLocked) != 0) {
        return QStringLiteral("locked");
    }
    return (flags & culina::c1link::kFlagLidClosed) != 0 ? QStringLiteral("closed")
                                                         : QStringLiteral("open");
}

bool DeviceViewModel::hotBowl() const {
    return runtime_.controller().hot_bowl();
}

QString DeviceViewModel::fault() const {
    return fault_name(runtime_.client().last_fault());
}

bool DeviceViewModel::awaitingUser() const {
    return runtime_.controller().awaiting_user();
}

int DeviceViewModel::progressCurrent() const {
    const std::size_t value = runtime_.controller().progress_current();
    return value > static_cast<std::size_t>(std::numeric_limits<int>::max())
               ? std::numeric_limits<int>::max()
               : static_cast<int>(value);
}

int DeviceViewModel::progressTotal() const {
    const std::size_t value = runtime_.controller().progress_total();
    return value > static_cast<std::size_t>(std::numeric_limits<int>::max())
               ? std::numeric_limits<int>::max()
               : static_cast<int>(value);
}

bool DeviceViewModel::startManual(double temperature_c, int speed, int minutes) {
    if (!connected_ || !std::isfinite(temperature_c) || speed < 0 || speed > 10 || minutes < 1 ||
        minutes > 1440 ||
        (temperature_c != 0.0 && (temperature_c < 37.0 || temperature_c > 160.0))) {
        return false;
    }
    const auto duration = static_cast<std::uint32_t>(minutes) * 60u;
    return runtime_.controller().start_manual(
               culina::from_celsius(static_cast<float>(temperature_c)),
               static_cast<std::uint8_t>(speed), duration) == culina::Status::Ok;
}

bool DeviceViewModel::startRecipe(int index) {
    if (!connected_ || index < 0) {
        return false;
    }
    const culina::app::Recipe* recipe = runtime_.recipes().at(static_cast<std::size_t>(index));
    return recipe != nullptr && runtime_.controller().start_recipe(recipe) == culina::Status::Ok;
}

void DeviceViewModel::nextStep() {
    if (runtime_.controller().awaiting_user()) {
        runtime_.controller().user_next();
    }
}

void DeviceViewModel::stop() {
    runtime_.controller().stop();
}

bool DeviceViewModel::tare() {
    return connected_ && runtime_.client().tare() == culina::Status::Ok;
}

bool DeviceViewModel::sendSimulatorCommand(const QString& command) {
    if (!controlConnected()) {
        simulator_status_ = QStringLiteral("Simulator controls disconnected");
        emit stateChanged();
        return false;
    }
    const QByteArray bytes = command.toUtf8() + '\n';
    if (control_.write(bytes) != bytes.size()) {
        simulator_status_ = QStringLiteral("Could not send simulator action");
        emit stateChanged();
        return false;
    }
    control_.flush();
    simulator_status_ = QStringLiteral("Applying action...");
    emit stateChanged();
    return true;
}

bool DeviceViewModel::addIngredient(double grams, const QString& ingredient) {
    static const QStringList ingredients = {QStringLiteral("water"), QStringLiteral("oil"),
                                            QStringLiteral("flour"), QStringLiteral("other")};
    if (!std::isfinite(grams) || grams < 0.1 || grams > 2200.0 ||
        !ingredients.contains(ingredient)) {
        return false;
    }
    return sendSimulatorCommand(QStringLiteral("add %1 %2").arg(grams, 0, 'f', 1).arg(ingredient));
}

bool DeviceViewModel::setLidOpen(bool open) {
    return sendSimulatorCommand(open ? QStringLiteral("lid open") : QStringLiteral("lid close"));
}

void DeviceViewModel::readSimulatorResponse() {
    while (control_.canReadLine()) {
        const QString response = QString::fromUtf8(control_.readLine()).trimmed();
        simulator_status_ =
            response == QStringLiteral("ok") ? QStringLiteral("Action applied") : response;
    }
    emit stateChanged();
}

void DeviceViewModel::requestShutdown() {
    if (ready_to_quit_ || shutdown_requested_) {
        return;
    }
    const auto state = runtime_.controller().state();
    if (state == culina::app::SessionState::Idle || state == culina::app::SessionState::Done) {
        finishShutdown();
        return;
    }
    shutdown_requested_ = true;
    shutdown_deadline_ms_ = clock_.now_ms() + 1000;
    runtime_.controller().stop();
}

void DeviceViewModel::finishShutdown() {
    ready_to_quit_ = true;
    timer_.stop();
    emit stateChanged();
    emit shutdownComplete();
}

void DeviceViewModel::refresh() {
    connected_ = uart_.connected();
    emit stateChanged();
}

void DeviceViewModel::tick() {
    clock_.advance_us(1000);
    runtime_.tick_1ms();
    if (++refresh_divider_ >= 25) {
        refresh_divider_ = 0;
        refresh();
    }
    if (shutdown_requested_) {
        const auto state = runtime_.controller().state();
        if (state == culina::app::SessionState::Done || state == culina::app::SessionState::Idle ||
            clock_.now_ms() >= shutdown_deadline_ms_) {
            finishShutdown();
        }
    }
}
