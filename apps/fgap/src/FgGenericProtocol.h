/*!
 * @file FgGenericProtocol.h
 *
 * @brief Generic prtocol for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified May 05, 2015
 */

#ifndef FGGENERICPROTOCOL_H
#define FGGENERICPROTOCOL_H

#include <QObject>
#include <QHash>
#include <QDebug>

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
