#include "modescentremodel.h"
#include "modescentreseserver.h"
#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ModesCentreModel>("modescentreserver", 1, 0, "ModesCentreModel");
    qmlRegisterType<ModesCentreSEServer>("modescentreserver", 1, 0, "ModesCentreServer");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/ModesCentreServer.qml"));
    QObject::connect(
    &engine, &QQmlApplicationEngine::objectCreated, &app,
    [url](QObject* obj, const QUrl& objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
