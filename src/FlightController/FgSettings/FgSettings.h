/*!
 * @file FgSettings.h
 *
 * @brief Settings class for using in QML
 * Can not use "Settings" from Qt.labs.settings because of lack of functionality
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Aug 27, 2015
 * @date Modified Aug 27, 2015
 */

#ifndef FGSETTINGS_H
#define FGSETTINGS_H

#include <QObject>

class FgSettings : public QObject
{
    Q_OBJECT
public:
    explicit FgSettings(QObject *parent = 0);
    ~FgSettings();

    QVariant property(const char *name) const;

signals:

public slots:
};

#endif // FGSETTINGS_H
