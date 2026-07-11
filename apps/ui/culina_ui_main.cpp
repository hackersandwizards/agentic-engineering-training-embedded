#include "device_view_model.h"

#include "sim/socket_transport.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QString>
#include <QTimer>

#include <cstdio>
#include <cstring>

int main(int argc, char** argv) {
    QQuickStyle::setStyle(QStringLiteral("Basic"));
    QGuiApplication app(argc, argv);

    const char* socket_path = "/tmp/c1link.sock";
    const char* control_socket_path = "/tmp/culina-control.sock";
    const char* recipe_dir = "data/recipes";
    bool smoke_test = false;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--socket") == 0 && i + 1 < argc) {
            socket_path = argv[++i];
        } else if (std::strcmp(argv[i], "--control-socket") == 0 && i + 1 < argc) {
            control_socket_path = argv[++i];
        } else if (std::strcmp(argv[i], "--recipes") == 0 && i + 1 < argc) {
            recipe_dir = argv[++i];
        } else if (std::strcmp(argv[i], "--smoke-test") == 0) {
            smoke_test = true;
        } else {
            std::fprintf(stderr,
                         "usage: %s [--socket path] [--control-socket path] [--recipes dir] "
                         "[--smoke-test]\n",
                         argv[0]);
            return 2;
        }
    }

    auto uart = culina::sim::SocketTransport::connect_to(socket_path);
    if (!uart.connected()) {
        std::fprintf(stderr, "no MCU at %s - start culina_mcu first\n", socket_path);
        return 1;
    }

    DeviceViewModel device(std::move(uart), QString::fromUtf8(control_socket_path),
                           QString::fromUtf8(recipe_dir));
    QQmlApplicationEngine engine;
    engine.setInitialProperties(
        {{QStringLiteral("device"), QVariant::fromValue(static_cast<QObject*>(&device))}});
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        [] { QCoreApplication::exit(1); }, Qt::QueuedConnection);
    QObject::connect(&device, &DeviceViewModel::shutdownComplete, &app, &QCoreApplication::quit);
    engine.loadFromModule(QStringLiteral("Culina"), QStringLiteral("Main"));
    QTimer smoke_timer;
    int smoke_attempts = 0;
    if (smoke_test) {
        smoke_timer.setInterval(10);
        QObject::connect(&smoke_timer, &QTimer::timeout, &app, [&] {
            if (device.hasTelemetry()) {
                smoke_timer.stop();
                device.requestShutdown();
            } else if (++smoke_attempts >= 200) {
                QCoreApplication::exit(1);
            }
        });
        smoke_timer.start();
    }
    return app.exec();
}
