/*!
 * @file log.h
 *
 * @brief Logging facilities
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 30, 2015
 * @date Modified Aug 27, 2015
 */

#ifndef FG_LOG
#define FG_LOG

#include <QFile>
#include <QDebug>
#include <QCoreApplication>

#include <iostream>

#define LOG_COLOR_RESET    "\033[0m"
#define LOG_COLOR_RED      "\033[31m"
#define LOG_COLOR_GREEN    "\033[32m"
#define LOG_COLOR_YELLOW   "\033[33m"
#define LOG_COLOR_BLUE     "\033[34m"
#define LOG_COLOR_PURPLE   "\033[35m"
#define LOG_COLOR_CYAN     "\033[36m"
#define LOG_COLOR_GRAY     "\033[37m"

inline void logMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
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
    QFile outFile(QCoreApplication::applicationDirPath() + "/fgautopilot.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;

    std::cout << txt.toStdString() << std::endl;
}

#endif // FG_LOG

