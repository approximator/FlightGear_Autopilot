#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "FgController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FgController fgController;
    QQmlApplicationEngine engine;
    QQmlContext *context=engine.rootContext();
    context->setContextProperty("fg_controller", &fgController);
    engine.load(QUrl(QStringLiteral("qrc:qml/MainView.qml")));

    return app.exec();
}
