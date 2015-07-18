/*!
 * @file pictorialindicatorwidget.cpp
 *
 * @brief Custom widget to represent a pictorial navigation indicator
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 16, 2015
 * @date Modified Jul 16, 2015
 */

#include "pictorialindicatorwidget.h"

#include <QCoreApplication>
#include <QVBoxLayout>
#include <QDebug>

PictorialIndicatorWidget::PictorialIndicatorWidget(QWidget *parent) : QWidget(parent)
{
    view.setSource(QUrl::fromLocalFile(FGAP_QML_RELATIVE_PATH "/FGear/Pointers/PictorialNavigation.qml"));

    QWidget *container = QWidget::createWindowContainer(&view, this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(container);
    this->setLayout(layout);

//    QObject *object = reinterpret_cast<QObject*>(view.rootObject());
//    connect(object, SIGNAL(autopilotEngage(bool)), this, SLOT(onEngage(bool)));
}

