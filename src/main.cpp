/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jul 30, 2015
 */

#include "FgAircraftsModel.h"
#include "log.h"

#include <QtQml>
#include <QApplication>

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    QApplication app(argc, argv);

    qmlRegisterType<FgAircraftsModel>("fgap", 1, 0, "FgAircraftsModel");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:qml/MainView.qml")));

    return app.exec();
}
