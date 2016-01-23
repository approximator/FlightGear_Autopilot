/*!
 * @file FgAutopilot.h
 *
 * @brief Basic autopilot class to inherit
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Jan 24, 2016
 */
#ifndef FGAUTOPILOT_H
#define FGAUTOPILOT_H

#include "QQmlVarPropertyHelpers.h"

#include <QObject>

class FgAutopilot : public QObject {
    Q_OBJECT
    QML_WRITABLE_VAR_PROPERTY(bool, engaged)
public:
    explicit FgAutopilot(QObject *parent = 0) : QObject(parent), m_engaged(false)
    {
    }

    virtual ~FgAutopilot()
    {
    }

    FgAutopilot(const FgAutopilot &other);
    FgAutopilot &operator=(const FgAutopilot &other);

    virtual void computeControl() = 0;
};

Q_DECLARE_METATYPE(FgAutopilot *)

#endif // FGAUTOPILOT_H
