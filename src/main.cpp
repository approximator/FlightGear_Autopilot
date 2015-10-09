/*!
 * @file main.cpp
 *
 * @brief FGAP entry point
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Sep 05, 2015
 */

#include "log.h"
#include "FgAircraftsModel.h"
#include "utils/Filesystem.h"

#include <QtQml>
#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
#ifdef FGAP_PLUGINS_PATH
    // Add path to search for Qt plugins
    QString pluginsPaths = fgap::path::join(
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
        QDir settingsDir = QFileInfo(settings.fileName()).absoluteDir();
        if (!settingsDir.exists())
            if (!settingsDir.mkpath(settingsDir.absolutePath()))
                qDebug() << "Could not create settings directory " << settingsDir.absolutePath();
        if (!QFile::exists(settings.fileName()))
        {
            QString configFileName(fgap::path::join(QCoreApplication::applicationDirPath(),
                                                    CONFIG_PATH,
                                                    "example_multiplayWithoutServer.ini"));
            qDebug() << "Copying "<< configFileName << " settings to " << settings.fileName();
            if (!QFile::copy(configFileName, settings.fileName()))
                qWarning() << "Could not copy default settings to " << settings.fileName();
        }
    }

    // Setup QML
    qmlRegisterType<FgAircraftsModel>("fgap", 1, 0, "FgAircraftsModel");
    QQmlApplicationEngine engine;
    QString qmlFilesPath = fgap::path::join(
                QCoreApplication::applicationDirPath(),
                FGAP_QML_MODULES_PATH);
    qDebug() << "qmlFilesPath = " << qmlFilesPath;
    engine.addImportPath(qmlFilesPath);
    engine.load(QUrl(QStringLiteral("qrc:qml/MainView.qml")));

    return app.exec();
}
