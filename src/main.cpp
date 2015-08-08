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
#include <QTextCodec>
#include <QApplication>

void logMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    Q_UNUSED(context);

    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(message);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(message);
        break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(message);
        break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(message);
        abort();
    }
    QFile outFile("log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qInstallMessageHandler(logMessageHandler);
    qmlRegisterType<FgAircraftsModel>("fgap", 1, 0, "FgAircraftsModel");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:qml/MainView.qml")));

    return app.exec();
}
