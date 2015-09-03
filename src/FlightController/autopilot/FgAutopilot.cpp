/*!
 * @file FgAutopilot.cpp
 *
 * @brief Basic autopilot class to inherit
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Sep 03, 2015
 */

#include "FgAutopilot.h"

FgAutopilot::FgAutopilot(QObject *parent) :
    QObject(parent)
{
}

void FgAutopilot::engage(bool enable)
{
    m_Engaged = enable;
}

void FgAutopilot::disengage()
{
    m_Engaged = false;
}

bool FgAutopilot::engaged()
{
    return m_Engaged;
}

