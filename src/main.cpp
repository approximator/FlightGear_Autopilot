/*!
 * @file main.cpp
 *
 * @brief FGAP entry point
 *
 *
 * Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 * Author: Andrii Shelest
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "FgAircraftsManager.h"
#include "log.h"
#include "utils/Filesystem.h"

#include <QApplication>
#include <QMessageBox>
#include <QTextCodec>
#include <QtQml>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
#ifdef APP_PLUGINS_PATH
    /* Add path to search for Qt plugins */
    QString pluginsPaths = fgap::path::join(QFileInfo(argv[0]).dir().path(), APP_PLUGINS_PATH);
    QCoreApplication::addLibraryPath(pluginsPaths);
#endif
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

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
            QString configFileName(":/config/example_multiplayWithoutServer.ini");
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

    QString qmlFilesPath = fgap::path::join(QCoreApplication::applicationDirPath(), APP_QML_MODULES_PATH);
    qDebug() << "qmlFilesPath = " << qmlFilesPath;
    engine.addImportPath(qmlFilesPath);
    engine.load(QUrl(QStringLiteral("qrc:qml/MainView.qml")));

    return success ? app.exec() : 1;
}
