/*!
 * @file FgGenericProtocol.cpp
 *
 * @brief Generic prtocol for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Aug 12, 2015
 */

#include "log.h"
#include "FgGenericProtocol.h"

#include <QMap>
#include <QPair>
#include <QFile>
#include <QXmlStreamWriter>

FgGenericProtocol::FgGenericProtocol(QObject *parent) :
    QObject(parent)
{
    // Parameters of instance that we control
    int index = 0;

#define ADD_PARAM(node, type) m_InParameters.insert(node, Parameter(index++, node, type));

    ADD_PARAM(CALLSIGN, Parameter::STRING);
    ADD_PARAM(HEADING, Parameter::FLOAT);
    ADD_PARAM(PITCH, Parameter::FLOAT);
    ADD_PARAM(ROLL, Parameter::FLOAT);
    ADD_PARAM(YAW, Parameter::FLOAT);
    ADD_PARAM(YAW_RATE, Parameter::FLOAT);
    ADD_PARAM(ALTITUDE, Parameter::FLOAT);
    ADD_PARAM(ALTITUDE_AGL, Parameter::FLOAT);
    ADD_PARAM(VERTICAL_SPEED, Parameter::FLOAT);
    ADD_PARAM(AIRSPEED, Parameter::FLOAT);
    ADD_PARAM(LATITUDE, Parameter::FLOAT);
    ADD_PARAM(LONGITUDE, Parameter::FLOAT);

    ADD_PARAM(DELTA_TIME, Parameter::FLOAT);
    ADD_PARAM(ELAPSED_TIME, Parameter::FLOAT);

    // other pilots' parameters
    // firstly, get actual number of other pilots
    ADD_PARAM(NUM_PLAYERS, Parameter::INT);
    ADD_PARAM(MODELS_COUNT, Parameter::INT);



    // TODO: fix this multiplayer stuff
//    for (int i = 0; i < 20; ++i)
//    {
//        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/callsign", Parameter::STRING);
//        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/heading-deg", Parameter::FLOAT);
//        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/pitch-deg", Parameter::FLOAT);
//        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/roll-deg", Parameter::FLOAT);
//        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/orientation/yaw-deg", Parameter::FLOAT);
//        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/position/altitude-ft", Parameter::INT);
//        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/position/altitude-agl-ft", Parameter::INT);
//        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/position/latitude-deg", Parameter::FLOAT);
//        ADD_PARAM("/ai/models/multiplayer[" + QString::number(i) + "]/position/longitude-deg", Parameter::FLOAT);
//    }

#undef ADD_PARAM


    // Parameteres to control
#define ADD_PARAM(node, type) m_OutParameters.insert(node, Parameter(index++, node, type));
    index = 0;
    ADD_PARAM(AILERONS, Parameter::FLOAT);
    ADD_PARAM(ELEVATOR, Parameter::FLOAT);
    ADD_PARAM(  RUDDER, Parameter::FLOAT);
//    ADD_PARAM(   WHEEL, Parameter::FLOAT);
    ADD_PARAM(THROTTLE, Parameter::FLOAT);
#undef ADD_PARAM
}

FgGenericProtocol::~FgGenericProtocol()
{
    qDebug() << "FgGenericProtocol detroyed.";
}

bool FgGenericProtocol::writeXml(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Can't open file for writing (" << fileName << ")";
        return false;
    }

    auto writeParameters = [](QXmlStreamWriter& stream, const QHash<QString, Parameter>& params) {
        std::vector<Parameter> temp;
        std::copy(std::begin(params), std::end(params), std::back_inserter(temp));
        std::sort(std::begin(temp), std::end(temp));
        std::for_each(std::begin(temp), std::end(temp), [&stream](const Parameter& param){
            stream.writeStartElement("chunk");
            stream.writeTextElement("name", param.name);
            stream.writeTextElement("node", param.name);
            stream.writeTextElement("type", param.typeStr());
            stream.writeTextElement("format", param.formatStr());
            stream.writeEndElement(); // chunk
        });
    };

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("PropertyList");
    stream.writeStartElement("generic");

    // output section
    stream.writeStartElement("output");
    stream.writeTextElement("line_separator", "newline");
    stream.writeTextElement("var_separator", "tab");
    writeParameters(stream, m_InParameters);
    stream.writeEndElement(); // output

    // input section
    stream.writeStartElement("input");
    stream.writeTextElement("line_separator", "newline");
    stream.writeTextElement("var_separator", "tab");
    writeParameters(stream, m_OutParameters);
    stream.writeEndElement(); // input

    stream.writeEndElement(); // generic
    stream.writeEndElement(); // PropertyList
    stream.writeEndDocument();
    file.close();

    qDebug() << "Protocol has been written to " << fileName;
    return true;
}

