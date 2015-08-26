/*!
 * @file FgSettings.cpp
 *
 * @brief Settings class for using in QML
 * Do not use "Settings" from Qt.labs.settings because of lack of functionality
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Aug 27, 2015
 * @date Modified Aug 27, 2015
 */

#include "log.h"
#include "FgSettings.h"

#include <QObject>
#include <QMetaProperty>

FgSettings::FgSettings(QObject *parent) : QObject(parent)
{
    qDebug() << "FgSettings created";
}

FgSettings::~FgSettings()
{
    QObject *object = this;
    const QMetaObject *metaobject = object->metaObject();
    int count = metaobject->propertyCount();
    for (int i=0; i<count; ++i) {
        QMetaProperty metaproperty = metaobject->property(i);
        const char *name = metaproperty.name();
        QVariant value = object->property(name);
        qDebug() << name << " = " << value;
    }
}

QVariant FgSettings::property(const char *name) const
{
    qDebug() << "Requested property: " << name;
    return QVariant();
}

