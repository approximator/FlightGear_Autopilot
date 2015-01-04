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

        Parameter(int i, ParamType t): index(i), type(t)
        {
        }

        QString typeStr() const
        {
            switch (type) {
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

        QString formatStr() const
        {
            switch (type) {
            case INT:
                return "%d";
            case FLOAT:
                return "%f";
            default:
                return "%s";
            }
        }

        int index;
        ParamType type;
    };

    explicit FgGenericProtocol(QObject *parent = 0);
    ~FgGenericProtocol();

    bool writeXml(const QString& fileName);

    QHash<QString, Parameter> m_Parameters; //! @todo make private

signals:

public slots:
};

#endif // FGGENERICPROTOCOL_H
