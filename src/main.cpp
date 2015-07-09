/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jul 09, 2015
 */

#include "FgController.h"
#include "Gui/widgets/mainwindow.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addOptions({
        {"oldstyle", QCoreApplication::translate("main", "Use old Widgets instead of QML")}
    });
    parser.process(app);

    if (parser.isSet("oldstyle"))
    {
        qDebug() << "Oldstyle";
        MainWindow w;
        w.show();
        return app.exec();
    }

    FgController fgController;
    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("fg_controller", &fgController);
    engine.load(QUrl(QStringLiteral("qrc:qml/MainView.qml")));
    fgController.init();
    return app.exec();
}
