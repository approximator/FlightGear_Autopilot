/*!
 * @file FgGenericProtocol.cpp
 *
 * @brief Generic prtocol for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Feb 17, 2015
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
    ADD_PARAM("/ai/models/count", Parameter::INT);

    // then do 20 iterations to get at most 20 other aircrafts
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


    // Parameteres to control
#define ADD_PARAM(node, type) m_OutParameters.insert(node, Parameter(index++, type));
    index = 0;
    ADD_PARAM("/controls/flight/aileron", Parameter::FLOAT);
    ADD_PARAM("/controls/flight/elevator", Parameter::FLOAT);

    writeXml("/usr/share/games/flightgear/Protocol/FgaOut.xml");
}

FgGenericProtocol::~FgGenericProtocol()
{
    qDebug() << "FgGenericProtocol detroyed.";
}

bool FgGenericProtocol::writeXml(const QString &fileName)
{
    QMap<int, QPair<QString, const Parameter*> > inParamsList;
    QMap<int, QPair<QString, const Parameter*> > outParamsList;

    { // copy parameters to QMap to get them sorted
        auto param = m_InParameters.constBegin();
        auto paramEnd = m_InParameters.constEnd();
        for (; param != paramEnd; ++param)
        {
            inParamsList.insert(param.value().index, qMakePair(param.key(), &param.value()));
        }

        param = m_OutParameters.constBegin();
        paramEnd = m_OutParameters.constEnd();
        for (; param != paramEnd; ++param)
        {
            outParamsList.insert(param.value().index, qMakePair(param.key(), &param.value()));
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

    // output section
    stream.writeStartElement("output");
    stream.writeTextElement("line_separator", "newline");
    stream.writeTextElement("var_separator", "tab");

    auto param = inParamsList.constBegin();
    auto paramEnd = inParamsList.constEnd();
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

    // input section
    stream.writeStartElement("input");
    stream.writeTextElement("line_separator", "newline");
    stream.writeTextElement("var_separator", "tab");
    param = outParamsList.constBegin();
    paramEnd = outParamsList.constEnd();
    for (; param != paramEnd; ++param)
    {
        stream.writeStartElement("chunk");
        stream.writeTextElement("name", param.value().first);
        stream.writeTextElement("node", param.value().first);
        stream.writeTextElement("type", param.value().second->typeStr());
        stream.writeTextElement("format", param.value().second->formatStr());
        stream.writeEndElement(); // chunk
    }
    stream.writeEndElement(); // input

    stream.writeEndElement(); // generic
    stream.writeEndElement(); // PropertyList

    stream.writeEndDocument();
    file.close();

    qDebug() << "Protocol has been written";
    return true;
}

