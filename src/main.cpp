/*!
 * @file main.cpp
 *
 * @brief FGAP entry point
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jan 24, 2016
 */

#include "log.h"
#include "FgAircraftsManager.h"
#include "utils/Filesystem.h"

#include <QtQml>
#include <QTextCodec>
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
#ifdef FGAP_PLUGINS_PATH
    /* Add path to search for Qt plugins */
    QString pluginsPaths = fgap::path::join(QFileInfo(argv[0]).dir().path(), FGAP_PLUGINS_PATH);
    QCoreApplication::addLibraryPath(pluginsPaths);
#endif

    QApplication app(argc, argv);
    qInstallMessageHandler(logMessageHandler);

    /* Set up settings */
    app.setOrganizationName("FlightgearAutopilot");
    app.setApplicationName("Flightgear_autopilot");
    QSettings::setDefaultFormat(QSettings::IniFormat);

    { /* Copy default setting if settings file does not exist */
        QSettings settings;
        QDir settingsDir = QFileInfo(settings.fileName()).absoluteDir();
        if (!settingsDir.exists())
            if (!settingsDir.mkpath(settingsDir.absolutePath()))
                qDebug() << "Could not create settings directory " << settingsDir.absolutePath();
        if (!QFile::exists(settings.fileName())) {
            QString configFileName(fgap::path::join(
                QCoreApplication::applicationDirPath(), CONFIG_PATH, "example_multiplayWithoutServer.ini"));
            qDebug() << "Copying " << configFileName << " settings to " << settings.fileName();
            if (!QFile::copy(configFileName, settings.fileName()))
                qWarning() << "Could not copy default settings to " << settings.fileName();
        }
    }

    /* Setup QML */
    bool success = true;
    qmlRegisterType<FgAircraftsManager>("fgap", 1, 0, "FgAircraftsManager");
    qRegisterMetaType<TAirModel *>("TAirModel*");
    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, [&success](QObject *object, const QUrl &url) {
        if (!object) {
            qWarning() << "Could not load QML";
            QMessageBox::critical(nullptr, "Flightgear autopilot", "<b>Flightgear autopilot</b> is failed to start due "
                                                                   "to errors in the main QML file.\n"
                                                                   "Please report the error following this link: "
                                                                   "<a "
                                                                   "href='https://github.com/approximator/"
                                                                   "FlightGear_Autopilot/issues/new'>"
                                                                   "https://github.com/approximator/"
                                                                   "FlightGear_Autopilot/issues/new</a>");
            success = false;
        } else
            qDebug() << "QML object created successfully: " << url;
    });

    QString qmlFilesPath = fgap::path::join(QCoreApplication::applicationDirPath(), FGAP_QML_MODULES_PATH);
    qDebug() << "qmlFilesPath = " << qmlFilesPath;
    engine.addImportPath(qmlFilesPath);
    engine.load(QUrl(QStringLiteral("qrc:qml/MainView.qml")));

    return success ? app.exec() : 1;
}
