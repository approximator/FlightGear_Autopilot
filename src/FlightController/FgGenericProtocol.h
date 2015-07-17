/*!
 * @file FgGenericProtocol.h
 *
 * @brief Generic prtocol for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jun 17, 2015
 */

#ifndef FGGENERICPROTOCOL_H
#define FGGENERICPROTOCOL_H

#include <QObject>
#include <QHash>
#include <QDebug>

const QString NUM_PLAYERS("/ai/models/num-players");
const QString MODELS_COUNT("/ai/models/count");

const QString CALLSIGN("/sim/multiplay/callsign");
const QString HEADING("/orientation/heading-deg");
const QString PITCH("/orientation/pitch-deg");
const QString ROLL("/orientation/roll-deg");
const QString YAW("/orientation/yaw-deg");
const QString ALTITUDE("/position/altitude-ft");
const QString ALTITUDE_AGL("/position/altitude-agl-ft");
const QString VERTICAL_SPEED("/velocities/vertical-speed-fps");
const QString AIRSPEED("/velocities/airspeed-kt");
const QString LATITUDE("/position/latitude-deg");
const QString LONGITUDE("/position/longitude-deg");

const QString AILERONS("/controls/flight/aileron");
const QString ELEVATOR("/controls/flight/elevator");
const QString RUDDER("/controls/flight/rudder");
const QString THROTTLE("/controls/engines/engine/throttle");


class FgGenericProtocol : public QObject
{
    Q_OBJECT
public:
    class Parameter
    {
    public:
        enum ParamType
        {
            INT = 0,
            FLOAT = 1,
            STRING
        } ;

        inline Parameter(int idx, ParamType t);
        inline const QString typeStr() const;
        inline const QString formatStr() const;

        int index;
        ParamType type;
    };

    explicit FgGenericProtocol(QObject *parent = 0);
    ~FgGenericProtocol();

    bool writeXml(const QString& fileName);
    inline int getParamIndex(const QString& node) const;

private:
    QHash<QString, Parameter> m_InParameters  { };
    QHash<QString, Parameter> m_OutParameters { };

signals:

public slots:
};


// Inline functions
int FgGenericProtocol::getParamIndex(const QString& node) const
{
//    qDebug() << "getParamIndex for node = " << node;
    return m_InParameters.value(node, Parameter(-1, Parameter::INT)).index;
}

FgGenericProtocol::Parameter::Parameter(int idx, ParamType t):
    index(idx),
    type(t)
{

}

const QString FgGenericProtocol::Parameter::typeStr() const
{
    switch (type)
    {
    case INT:
        return "int";
    case FLOAT:
        return "float";
    case STRING:
        return "string";
    default:
        return "unknown";
        break;
    }
}

const QString FgGenericProtocol::Parameter::formatStr() const
{
    switch (type)
    {
    case INT:
        return "%d";
    case FLOAT:
        return "%f";
    default:
        return "%s";
    }
}

#endif // FGGENERICPROTOCOL_H
