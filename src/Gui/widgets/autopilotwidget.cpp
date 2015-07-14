/*!
 * @file aircraftwidget.cpp
 *
 * @brief Custom widget to represent an autopilot panel
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 14, 2015
 * @date Modified Jul 14, 2015
 */

#include "autopilotwidget.h"

#include <QQmlComponent>
#include <QWidget>
#include <QVBoxLayout>
#include <QQuickItem>
#include <QQuickWindow>
#include <QQuickView>
#include <QDebug>

AutopilotWidget::AutopilotWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    QQuickView *view = new QQuickView;
    QWidget *container = QWidget::createWindowContainer(view, this);
    view->setSource(QUrl(QCoreApplication::applicationDirPath() + "/qml/FGear/FgAutopilot.qml"));
    layout->addWidget(container);
    this->setLayout(layout);
}

