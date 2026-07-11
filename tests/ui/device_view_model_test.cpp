#include "device_view_model.h"

#include "sim/sim_board.h"
#include "sim/sim_control_server.h"
#include "sim/socket_transport.h"

#include <QCoreApplication>
#include <QTest>

#include <memory>
#include <string>
#include <unistd.h>

class DeviceViewModelTest final : public QObject {
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void validatesManualCookingInputs();
    void exposesAndStartsRecipes();
    void sendsPhysicalActionsToTheSimulationChannel();

private:
    std::unique_ptr<DeviceViewModel> makeModel(bool with_control = false);

    std::string c1_path_;
    std::string control_path_;
    culina::sim::SimBoard board_;
    std::unique_ptr<culina::sim::SocketTransport> mcu_transport_;
    std::unique_ptr<culina::sim::SimControlServer> control_server_;
};

void DeviceViewModelTest::init() {
    const std::string suffix = std::to_string(::getpid());
    c1_path_ = "/tmp/culina-view-model-" + suffix + ".sock";
    control_path_ = "/tmp/culina-view-control-" + suffix + ".sock";
    mcu_transport_ = std::make_unique<culina::sim::SocketTransport>(
        culina::sim::SocketTransport::listen_on(c1_path_.c_str()));
    QVERIFY(mcu_transport_->valid());
}

void DeviceViewModelTest::cleanup() {
    control_server_.reset();
    mcu_transport_.reset();
    ::unlink(c1_path_.c_str());
    ::unlink(control_path_.c_str());
}

std::unique_ptr<DeviceViewModel> DeviceViewModelTest::makeModel(bool with_control) {
    if (with_control) {
        control_server_ = std::make_unique<culina::sim::SimControlServer>(
            culina::sim::SimControlServer::listen_on(control_path_.c_str(), &board_));
    }
    auto app_transport = culina::sim::SocketTransport::connect_to(c1_path_.c_str());
    return std::make_unique<DeviceViewModel>(std::move(app_transport),
                                             QString::fromStdString(control_path_),
                                             QStringLiteral(CULINA_DATA_DIR "/recipes"));
}

void DeviceViewModelTest::validatesManualCookingInputs() {
    auto model = makeModel();
    QVERIFY(model->connected());
    QVERIFY(!model->startManual(20.0, 2, 15));
    QVERIFY(!model->startManual(80.0, 11, 15));
    QVERIFY(!model->startManual(80.0, 2, 0));
    QVERIFY(model->startManual(80.0, 2, 15));
}

void DeviceViewModelTest::exposesAndStartsRecipes() {
    auto model = makeModel();
    QVERIFY(!model->recipeNames().isEmpty());
    QVERIFY(!model->startRecipe(-1));
    QVERIFY(!model->startRecipe(static_cast<int>(model->recipeNames().size())));
    QVERIFY(model->startRecipe(0));
}

void DeviceViewModelTest::sendsPhysicalActionsToTheSimulationChannel() {
    auto model = makeModel(true);
    QTRY_VERIFY(model->controlConnected());
    QVERIFY(model->addIngredient(250.0, QStringLiteral("flour")));
    for (int i = 0; i < 20; ++i) {
        control_server_->poll();
        QCoreApplication::processEvents();
    }
    QCOMPARE(board_.true_mass_g(), 250.0f);

    QVERIFY(model->setLidOpen(true));
    for (int i = 0; i < 20; ++i) {
        control_server_->poll();
        QCoreApplication::processEvents();
    }
    QVERIFY(!board_.lid_closed());
}

QTEST_GUILESS_MAIN(DeviceViewModelTest)

#include "device_view_model_test.moc"
