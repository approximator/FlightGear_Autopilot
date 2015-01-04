/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jan 04, 2015
 */

#include "FgAircraft.h"

#include <QDebug>

FgAircraft::FgAircraft(QObject *parent) :
    QObject(parent),
    m_Callsign("(none)")
{

}

FgAircraft::~FgAircraft()
{
    qDebug() << m_Callsign << " destroyed.";
}

