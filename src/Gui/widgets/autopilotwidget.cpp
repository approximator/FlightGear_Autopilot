/*!
 * @file aircraftwidget.cpp
 *
 * @brief Custom widget to represent an autopilot panel
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 14, 2015
 * @date Modified Jul 20, 2015
 */

#include "autopilotwidget.h"

#include <QCoreApplication>
#include <QVBoxLayout>
#include <QDebug>

AutopilotWidget::AutopilotWidget(QWidget *parent) : QWidget(parent)
{
    QString qmlFilename("%1/%2/%3");
    qmlFilename = qmlFilename.arg(QCoreApplication::applicationDirPath(),
                                  FGAP_QML_RELATIVE_PATH,
                                  "FGear/FgAutopilot.qml");

    view.setSource(QUrl::fromLocalFile(qmlFilename));

    QWidget *container = QWidget::createWindowContainer(&view, this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(container);
    this->setLayout(layout);

    QObject *object = reinterpret_cast<QObject*>(view.rootObject());
    connect(object, SIGNAL(autopilotEngage(bool)), this, SLOT(onEngage(bool)));
}

void AutopilotWidget::onEngage(bool engage)
{
    emit autopilotEngage(engage);
}


