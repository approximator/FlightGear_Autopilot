/*!
 * @file main.cpp
 *
 * @brief FGAP entry point
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Aug 27, 2015
 */

#include "log.h"
#include "FgAircraftsModel.h"

#include <QtQml>
#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
#ifdef FGAP_PLUGINS_PATH
    // Add path to search for Qt plugins
    QString pluginsPaths = QString("%1/%2").arg(
                QFileInfo(argv[0]).dir().path(),
                FGAP_PLUGINS_PATH);
    QCoreApplication::addLibraryPath(pluginsPaths);
#endif

    QApplication app(argc, argv);
    qInstallMessageHandler(logMessageHandler);

    // Set up settings
    app.setOrganizationName("FlightgearAutopilot");
    app.setApplicationName("Flightgear_autopilot");
    QSettings::setDefaultFormat(QSettings::IniFormat);

    { // Copy default setting if settings file does not exist
        QSettings settings;
        if (!QFile::exists(settings.fileName()))
        {
            QString configFileName("%1/%2/%3");
            configFileName = configFileName.arg(QCoreApplication::applicationDirPath(), CONFIG_PATH,
                                                "DefaultSettings.ini");
            qDebug() << "Copying default settings to " << settings.fileName();
            if (!QFile::copy(configFileName, settings.fileName()))
                qWarning() << "Could not copy default settings to " << settings.fileName();
        }
    }

    // Setup QML
    qmlRegisterType<FgAircraftsModel>("fgap", 1, 0, "FgAircraftsModel");
    QQmlApplicationEngine engine;
    QString qmlFilesPath = QString("%1/%2").arg(
                QCoreApplication::applicationDirPath(),
                FGAP_QML_MODULES_PATH);
    engine.addImportPath(qmlFilesPath);
    engine.load(QUrl(QStringLiteral("qrc:qml/MainView.qml")));

    return app.exec();
}
