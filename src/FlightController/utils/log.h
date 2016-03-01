/*!
 * @file log.h
 *
 * @brief Logging facilities
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

#ifndef FG_LOG
#define FG_LOG

#include <QFile>
#include <QDebug>
#include <QCoreApplication>

#include <iostream>

#define LOG_COLOR_RESET "\033[0m"
#define LOG_COLOR_RED "\033[31m"
#define LOG_COLOR_GREEN "\033[32m"
#define LOG_COLOR_YELLOW "\033[33m"
#define LOG_COLOR_BLUE "\033[34m"
#define LOG_COLOR_PURPLE "\033[35m"
#define LOG_COLOR_CYAN "\033[36m"
#define LOG_COLOR_GRAY "\033[37m"

inline void logMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message)
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
            /* for Qt 5.5 it will be 'case QtInfoMsg:' */
            txt = QString("%1Info: %2").arg(LOG_COLOR_RESET).arg(message);
            break;
    }

    /* FIXME to determine right location of this file! */
    QFile outFile(QCoreApplication::applicationDirPath() + "/fgautopilot.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;

    std::cout << txt.toStdString() << std::endl;
}

#endif /* FG_LOG */
