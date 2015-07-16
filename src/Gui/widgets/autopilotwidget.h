/*!
 * @file aircraftwidget.h
 *
 * @brief Custom widget to represent an autopilot panel
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 14, 2015
 * @date Modified Jul 16, 2015
 */

#ifndef AUTOPILOTWIDGET_H
#define AUTOPILOTWIDGET_H

#include <QWidget>
#include <QQuickView>

class AutopilotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutopilotWidget(QWidget *parent = 0);

private:
    AutopilotWidget(const AutopilotWidget& other);
    AutopilotWidget& operator=(const AutopilotWidget& other);

    QQuickView view { };

signals:
    void autopilotEngage(bool);

private slots:
    void onEngage(bool engage);

public slots:
};

#endif // AUTOPILOTWIDGET_H
