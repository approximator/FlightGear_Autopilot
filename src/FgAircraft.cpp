/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Feb 12, 2015
 */

#include "FgAircraft.h"

#include <QDebug>

FgAircraft::FgAircraft(const QString& sign, QObject *parent) :
    QObject(parent),
    m_Callsign(sign),
    m_Index(-1)
{
    qDebug() << callsign() << " created";
}

FgAircraft::~FgAircraft()
{
    qDebug() << m_Callsign << " destroyed.";
}

