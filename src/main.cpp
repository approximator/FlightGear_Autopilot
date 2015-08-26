/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Aug 26, 2015
 */

#include "log.h"
#include "FgAircraftsModel.h"
#include "FgSettings/FgSettings.h"

#include <QtQml>
#include <QTextCodec>
#include <QApplication>

#include <iostream>

void logMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    Q_UNUSED(context);

    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("%1Debug: %2").arg(LOG_COLOR_GREEN).arg(message);
        break;
    case QtWarningMsg:
        txt = QString("%1Warning: %2").arg(LOG_COLOR_CYAN).arg(message);
        break;
    case QtCriticalMsg:
        txt = QString("%1Critical: %2").arg(LOG_COLOR_PURPLE).arg(message);
        break;
    case QtFatalMsg:
        txt = QString("%1Fatal: %2").arg(LOG_COLOR_RED).arg(message);
        abort();
    default:
    // for Qt 5.5 it will be 'case QtInfoMsg:'
        txt = QString("%1Info: %2").arg(LOG_COLOR_RESET).arg(message);
        break;
    }

/*FIXME to determine right location of this file!!!*/
//    QFile outFile("log");
//    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
//    QTextStream ts(&outFile);
//    ts << txt << endl;

    std::cout << txt.toStdString() << std::endl;
}

int main(int argc, char *argv[])
{
    QString pluginsPaths = QString("%1/%2").arg(
                QFileInfo(argv[0]).dir().path(),
                FGAP_PLUGINS_PATH);
    QCoreApplication::addLibraryPath(pluginsPaths);

    QApplication app(argc, argv);
    app.setOrganizationName("FlightgearAutopilot");
    app.setApplicationName("Flightgear_autopilot");
    QSettings::setDefaultFormat(QSettings::IniFormat);

    qInstallMessageHandler(logMessageHandler);

    qmlRegisterType<FgAircraftsModel>("fgap.aircraftsmodel", 1, 0, "AircraftsModel");
    qmlRegisterType<FgSettings>("fgap.settings", 1, 0, "Settings");
    QQmlApplicationEngine engine;
    QString qmlFilesPath = QString("%1/%2").arg(
                QCoreApplication::applicationDirPath(),
                FGAP_QML_MODULES_PATH);
    engine.addImportPath(qmlFilesPath);
    engine.load(QUrl(QStringLiteral("qrc:qml/MainView.qml")));

    return app.exec();
}
