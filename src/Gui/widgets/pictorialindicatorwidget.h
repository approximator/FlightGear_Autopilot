/*!
 * @file pictorialindicatorwidget.h
 *
 * @brief Custom widget to represent a pictorial navigation indicator
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 16, 2015
 * @date Modified Jul 16, 2015
 */

#ifndef PICTORIALINDICATORWIDGET_H
#define PICTORIALINDICATORWIDGET_H

#include <QWidget>
#include <QQuickView>

class PictorialIndicatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PictorialIndicatorWidget(QWidget *parent = 0);

private:
    QQuickView view { };

signals:

public slots:
};

#endif // PICTORIALINDICATORWIDGET_H
