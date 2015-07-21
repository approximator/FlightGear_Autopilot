/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jul 21, 2015
 */

#include "FgAircraftsModel.h"
#include "Gui/widgets/mainwindow.h"

#include <QtQml>
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addOptions({
        {"widgets", QCoreApplication::translate("main", "Use old Widgets instead of QML")}
    });
    parser.process(app);

    if (parser.isSet("widgets") || !QString(qgetenv("FGAP_USE_WIDGETS_UI")).isEmpty())
    {
        MainWindow w;
        w.show();
        return app.exec();
    }

    qmlRegisterType<FgAircraftsModel>("fgap", 1, 0, "FgAircraftsModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:qml/MainView.qml")));

    return app.exec();
}
