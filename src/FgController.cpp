#include "FgController.h"
#include "FgTransport.h"

FgController::FgController(QObject *parent) :
    QObject(parent),
    m_Transport(0)
{
    m_Transport = new FgTransport(this);
    //! @todo Connections!!
    connect(m_Transport, SIGNAL(fgDataReceived(QString)), this, SLOT(parseFgData(QString)));
}

void FgController::updateAircraft(const QString &aircraftId)
{
    if (!m_Aircrafts.isEmpty())
    {
        FgAircraft *aircraft = m_Aircrafts.value(aircraftId);
        emit aircraftUpdateded(aircraft);
    }
}

void FgController::parseFgData(const QString &data)
{
    if (!m_Aircrafts.contains(data))
    {
        FgAircraft *newAircraft = new FgAircraft(data);
        m_Aircrafts[data] = newAircraft;
        emit aircraftConnected(newAircraft);
    }
    else
    {
        emit aircraftUpdateded(m_Aircrafts.value(data));
    }
}
