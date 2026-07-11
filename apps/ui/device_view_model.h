#pragma once

#include "app/application_runtime.h"
#include "sim/sim_clock.h"
#include "sim/socket_transport.h"

#include <QLocalSocket>
#include <QObject>
#include <QStringList>
#include <QTimer>

class DeviceViewModel final : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected NOTIFY stateChanged)
    Q_PROPERTY(bool hasTelemetry READ hasTelemetry NOTIFY stateChanged)
    Q_PROPERTY(bool controlConnected READ controlConnected NOTIFY stateChanged)
    Q_PROPERTY(bool readyToQuit READ readyToQuit NOTIFY stateChanged)
    Q_PROPERTY(QString sessionState READ sessionState NOTIFY stateChanged)
    Q_PROPERTY(QString programName READ programName NOTIFY stateChanged)
    Q_PROPERTY(QString programStatus READ programStatus NOTIFY stateChanged)
    Q_PROPERTY(double temperature READ temperature NOTIFY stateChanged)
    Q_PROPERTY(int weight READ weight NOTIFY stateChanged)
    Q_PROPERTY(int rpm READ rpm NOTIFY stateChanged)
    Q_PROPERTY(QString lidState READ lidState NOTIFY stateChanged)
    Q_PROPERTY(bool hotBowl READ hotBowl NOTIFY stateChanged)
    Q_PROPERTY(QString fault READ fault NOTIFY stateChanged)
    Q_PROPERTY(bool awaitingUser READ awaitingUser NOTIFY stateChanged)
    Q_PROPERTY(int progressCurrent READ progressCurrent NOTIFY stateChanged)
    Q_PROPERTY(int progressTotal READ progressTotal NOTIFY stateChanged)
    Q_PROPERTY(QStringList recipeNames READ recipeNames CONSTANT)
    Q_PROPERTY(QString simulatorStatus READ simulatorStatus NOTIFY stateChanged)

public:
    DeviceViewModel(culina::sim::SocketTransport uart, const QString& control_socket,
                    const QString& recipe_dir, QObject* parent = nullptr);

    bool connected() const { return connected_; }
    bool hasTelemetry() const { return runtime_.telemetry().has_data(); }
    bool controlConnected() const;
    bool readyToQuit() const { return ready_to_quit_; }
    QString sessionState() const;
    QString programName() const;
    QString programStatus() const;
    double temperature() const;
    int weight() const;
    int rpm() const;
    QString lidState() const;
    bool hotBowl() const;
    QString fault() const;
    bool awaitingUser() const;
    int progressCurrent() const;
    int progressTotal() const;
    QStringList recipeNames() const { return recipe_names_; }
    QString simulatorStatus() const { return simulator_status_; }

    Q_INVOKABLE bool startManual(double temperature_c, int speed, int minutes);
    Q_INVOKABLE bool startRecipe(int index);
    Q_INVOKABLE void nextStep();
    Q_INVOKABLE void stop();
    Q_INVOKABLE bool tare();
    Q_INVOKABLE bool addIngredient(double grams, const QString& ingredient);
    Q_INVOKABLE bool setLidOpen(bool open);
    Q_INVOKABLE void requestShutdown();

signals:
    void stateChanged();
    void shutdownComplete();

private slots:
    void tick();
    void readSimulatorResponse();

private:
    class AppWatchdog final : public culina::hal::IWatchdog {
    public:
        void feed() override {}
        culina::Millis timeout_ms() const override { return 500; }
    };

    void refresh();
    bool sendSimulatorCommand(const QString& command);
    void finishShutdown();

    culina::sim::SocketTransport uart_;
    culina::sim::SimClock clock_;
    AppWatchdog watchdog_;
    culina::app::ApplicationRuntime runtime_;
    QLocalSocket control_;
    QTimer timer_;
    QStringList recipe_names_;
    QString simulator_status_;
    bool connected_ = false;
    bool shutdown_requested_ = false;
    bool ready_to_quit_ = false;
    culina::Millis shutdown_deadline_ms_ = 0;
    int refresh_divider_ = 0;
};
