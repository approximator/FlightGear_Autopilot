/*!
 * @file FgGenericProtocol.cpp
 *
 * @brief Generic prtocol for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Feb 14, 2015
 */

#include "FgGenericProtocol.h"

#include <QXmlStreamWriter>
#include <QPair>
#include <QFile>
#include <QDebug>

FgGenericProtocol::FgGenericProtocol(QObject *parent) :
    QObject(parent),
    m_InParameters(),
    m_OutParameters()
{
    // Parameters of instance that we control
    int index = 0;

#define ADD_PARAM(node, type) m_InParameters.insert(node, Parameter(index++, type));

    ADD_PARAM("/sim/multiplay/callsign", Parameter::STRING);
    ADD_PARAM("/orientation/heading-deg", Parameter::FLOAT);
    ADD_PARAM("/orientation/pitch-deg", Parameter::FLOAT);
    ADD_PARAM("/orientation/roll-deg", Parameter::FLOAT);
    ADD_PARAM("/orientation/yaw-deg", Parameter::FLOAT);
    ADD_PARAM("/position/altitude-ft", Parameter::INT);
    ADD_PARAM("/position/latitude-deg", Parameter::FLOAT);
    ADD_PARAM("/position/longitude-deg", Parameter::FLOAT);

    // other pilots' parameters
    // firstly, get actual number of other pilots
    ADD_PARAM("/ai/models/num-players", Parameter::INT);
//    ADD_PARAM("/ai/models/count", Parameter::INT);

    // then do 20 iterations to get at most 20 other aircrafts
    ADD_PARAM("/ai/models/multiplayer/callsign", Parameter::STRING);
    ADD_PARAM("/ai/models/multiplayer/orientation/heading-deg", Parameter::FLOAT);
    ADD_PARAM("/ai/models/multiplayer/orientation/pitch-deg", Parameter::FLOAT);
    ADD_PARAM("/ai/models/multiplayer/orientation/roll-deg", Parameter::FLOAT);
    ADD_PARAM("/ai/models/multiplayer/orientation/yaw-deg", Parameter::FLOAT);
    ADD_PARAM("/ai/models/multiplayer/position/altitude-ft", Parameter::INT);
    ADD_PARAM("/ai/models/multiplayer/position/latitude-deg", Parameter::FLOAT);
    ADD_PARAM("/ai/models/multiplayer/position/longitude-deg", Parameter::FLOAT);
    for (int i = 0; i < 20; ++i)
    {
        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/callsign", Parameter::STRING);
        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/heading-deg", Parameter::FLOAT);
        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/pitch-deg", Parameter::FLOAT);
        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/roll-deg", Parameter::FLOAT);
        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/yaw-deg", Parameter::FLOAT);
        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/position/altitude-ft", Parameter::INT);
        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/position/latitude-deg", Parameter::FLOAT);
        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/position/longitude-deg", Parameter::FLOAT);
    }

//    /velocities/airspeed-kt

#undef ADD_PARAM

    writeXml("/usr/share/games/flightgear/Protocol/FgaOut.xml");
}

FgGenericProtocol::~FgGenericProtocol()
{
    qDebug() << "FgGenericProtocol detroyed.";
}

bool FgGenericProtocol::writeXml(const QString &fileName)
{
    QMap<int, QPair<QString, const Parameter*> > tmpList;

    { // copy parameters to QMap to get them sorted
        QHash<QString, Parameter>::const_iterator param = m_InParameters.constBegin();
        QHash<QString, Parameter>::const_iterator paramEnd = m_InParameters.constEnd();
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

