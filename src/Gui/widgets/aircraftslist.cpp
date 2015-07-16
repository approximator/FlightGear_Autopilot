/*!
 * @file aircraftslist.cpp
 *
 * @brief Custom widget implementation to represent an aircrafts list
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 09, 2015
 * @date Modified Jul 16, 2015
 */

#include "FgAircraft.h"
#include "FgControlledAircraft.h"
#include "aircraftslist.h"

#include <QLabel>
#include <QLayout>
#include <QPushButton>

AircraftsList::AircraftsList(QWidget *parent) : QListWidget(parent)
{
    connect(this, &AircraftsList::currentItemChanged, this, &AircraftsList::itemChanged);
}

void AircraftsList::addAircraft(FgAircraft *aircraft)
{
    QListWidgetItem* item = new QListWidgetItem(this);
    item->setData(Qt::UserRole, qVariantFromValue(static_cast<void *>(aircraft)));

    QWidget *widget = new QWidget;

    QHBoxLayout *layout = new QHBoxLayout;
    auto label = new QLabel(aircraft->callsign());
    layout->addWidget(label);

    auto ourAircraft = dynamic_cast<FgControlledAircraft*>(aircraft);
    if (ourAircraft)
    {
        auto button = new QPushButton("Run");
        button->setFlat(true);
        button->setCheckable(true);
        layout->addWidget(button);
        connect(button, &QPushButton::toggled, ourAircraft, &FgControlledAircraft::runFlightGear);
        connect(ourAircraft, &FgControlledAircraft::flightgearStarted, [this, button](){ button->setText("Running"); });
        connect(ourAircraft, &FgControlledAircraft::flightgearFinished, [this, button](){ button->setText("Finished"); });
    }

    widget->resize(0, 65);
    item->setSizeHint(widget->size());

    widget->setLayout(layout);
    setItemWidget(item, widget);
    addItem(item);
}

void AircraftsList::itemChanged(QListWidgetItem *current, QListWidgetItem * /*previous*/)
{
    FgAircraft *aircraft = static_cast<FgAircraft*>(current->data(Qt::UserRole).value<void *>());
    emit aircraftSelected(aircraft);
}

FgAircraft *AircraftsList::currentAircraft()
{
    return static_cast<FgAircraft*>(currentItem()->data(Qt::UserRole).value<void *>());
}

void AircraftsList::updateAircraft(FgAircraft *aircraft)
{
    qDebug() << aircraft->callsign() << " updated";
}

void AircraftsList::removeAircraft(FgAircraft *aircraft)
{
    qDebug() << aircraft->callsign() << " removed";
}


