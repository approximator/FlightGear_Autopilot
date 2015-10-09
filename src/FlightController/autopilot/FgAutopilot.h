/*!
 * @file FgAutopilot.h
 *
 * @brief Basic autopilot class to inherit
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Oct 05, 2015
 */
#ifndef FGAUTOPILOT_H
#define FGAUTOPILOT_H

#include <QObject>

class FgAutopilot : public QObject
{
    Q_OBJECT
public:
    explicit FgAutopilot(QObject *parent = 0);
    FgAutopilot(const FgAutopilot& other);
    FgAutopilot& operator=(const FgAutopilot& other);

    Q_INVOKABLE void engage(bool enable = true);
    Q_INVOKABLE void disengage();
    Q_INVOKABLE bool engaged();

    virtual void computeControl() = 0;

private:
    bool m_Engaged { false };
};

Q_DECLARE_METATYPE(FgAutopilot *)

#endif // FGAUTOPILOT_H
