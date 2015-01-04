/*!
 * @file FgGenericProtocol.cpp
 *
 * @brief Generic prtocol for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jan 04, 2015
 */

#include "FgGenericProtocol.h"

#include <QXmlStreamWriter>
#include <QLinkedList>
#include <QPair>
#include <QFile>
#include <QDebug>

FgGenericProtocol::FgGenericProtocol(QObject *parent) : QObject(parent)
{
    // Parameters of instance than we control
    int index = 0;

    m_Parameters.insert("/sim/multiplay/callsign", Parameter(index++, Parameter::STRING));
    m_Parameters.insert("/orientation/heading-deg", Parameter(index++, Parameter::FLOAT));
    m_Parameters.insert("/orientation/pitch-deg", Parameter(index++, Parameter::FLOAT));
    m_Parameters.insert("/orientation/roll-deg", Parameter(index++, Parameter::FLOAT));
    m_Parameters.insert("/orientation/yaw-deg", Parameter(index++, Parameter::FLOAT));
    m_Parameters.insert("/position/altitude-ft", Parameter(index++, Parameter::INT));
    m_Parameters.insert("/position/latitude-deg", Parameter(index++, Parameter::FLOAT));
    m_Parameters.insert("/position/longitude-deg", Parameter(index++, Parameter::FLOAT));

    // other pilots' parameters
    // firstly, get actual number of other pilots
    m_Parameters.insert("/ai/models/num-players", Parameter(index++, Parameter::INT));

    // then do 20 iterations to get at most 20 other aircrafts
    m_Parameters.insert("/ai/models/multiplayer/callsign", Parameter(index++, Parameter::STRING));
    m_Parameters.insert("/ai/models/multiplayer/orientation/heading-deg", Parameter(index++, Parameter::FLOAT));
    m_Parameters.insert("/ai/models/multiplayer/orientation/pitch-deg", Parameter(index++, Parameter::FLOAT));
    m_Parameters.insert("/ai/models/multiplayer/orientation/roll-deg", Parameter(index++, Parameter::FLOAT));
    m_Parameters.insert("/ai/models/multiplayer/orientation/yaw-deg", Parameter(index++, Parameter::FLOAT));
    m_Parameters.insert("/ai/models/multiplayer/position/altitude-ft", Parameter(index++, Parameter::INT));
    m_Parameters.insert("/ai/models/multiplayer/position/latitude-deg", Parameter(index++, Parameter::FLOAT));
    m_Parameters.insert("/ai/models/multiplayer/position/longitude-deg", Parameter(index++, Parameter::FLOAT));
    for (int i = 0; i < 20; ++i)
    {
        m_Parameters.insert("/ai/models/multiplayer[" + QString::number(i) + "]/callsign", Parameter(index++, Parameter::STRING));
        m_Parameters.insert("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/heading-deg", Parameter(index++, Parameter::FLOAT));
        m_Parameters.insert("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/pitch-deg", Parameter(index++, Parameter::FLOAT));
        m_Parameters.insert("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/roll-deg", Parameter(index++, Parameter::FLOAT));
        m_Parameters.insert("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/yaw-deg", Parameter(index++, Parameter::FLOAT));
        m_Parameters.insert("/ai/models/multiplayer[" + QString::number(i) + "]/position/altitude-ft", Parameter(index++, Parameter::INT));
        m_Parameters.insert("/ai/models/multiplayer[" + QString::number(i) + "]/position/latitude-deg", Parameter(index++, Parameter::FLOAT));
        m_Parameters.insert("/ai/models/multiplayer[" + QString::number(i) + "]/position/longitude-deg", Parameter(index++, Parameter::FLOAT));
    }

//    /velocities/airspeed-kt
}

FgGenericProtocol::~FgGenericProtocol()
{
    qDebug() << "FgGenericProtocol detroyed.";
}

bool FgGenericProtocol::writeXml(const QString &fileName)
{
    QMap<int, QPair<QString, const Parameter*> > tmpList;

    { // copy parameters to QMap to get them sorted
        QHash<QString, Parameter>::const_iterator param = m_Parameters.constBegin();
        QHash<QString, Parameter>::const_iterator paramEnd = m_Parameters.constEnd();
        for (; param != paramEnd; ++param)
        {
            tmpList.insert(param.value().index, qMakePair(param.key(), &param.value()));
        }
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Can't open file for writing (" << fileName << ")";
        return false;
    }

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    stream.writeStartElement("PropertyList");
    stream.writeStartElement("generic");
    stream.writeStartElement("output");
    stream.writeTextElement("line_separator", "newline");
    stream.writeTextElement("var_separator", "tab");

    QMap<int, QPair<QString, const Parameter*> >::const_iterator param = tmpList.constBegin();
    QMap<int, QPair<QString, const Parameter*> >::const_iterator paramEnd = tmpList.constEnd();
    for (; param != paramEnd; ++param)
    {
        stream.writeStartElement("chunk");
        stream.writeTextElement("name", param.value().first);
        stream.writeTextElement("node", param.value().first);
        stream.writeTextElement("type", param.value().second->typeStr());
        stream.writeTextElement("format", param.value().second->formatStr());
        stream.writeEndElement(); // chunk
    }

    stream.writeEndElement(); // output
    stream.writeEndElement(); // generic
    stream.writeEndElement(); // PropertyList

    stream.writeEndDocument();
    file.close();

    qDebug() << "Protocol has been written";
    return true;
}

