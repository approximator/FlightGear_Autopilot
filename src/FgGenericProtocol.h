/*!
 * @file FgGenericProtocol.h
 *
 * @brief Generic prtocol for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jan 04, 2015
 */

#ifndef FGGENERICPROTOCOL_H
#define FGGENERICPROTOCOL_H

#include <QObject>
#include <QHash>

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

        Parameter(int idx, ParamType t): index(idx), type(t) {}
        inline const QString typeStr() const;
        inline const QString formatStr() const;

        int index;
        ParamType type;
    };

    explicit FgGenericProtocol(QObject *parent = 0);
    ~FgGenericProtocol();

    bool writeXml(const QString& fileName);

private:
    QHash<QString, Parameter> m_Parameters;

signals:

public slots:
};


// Inline functions
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
