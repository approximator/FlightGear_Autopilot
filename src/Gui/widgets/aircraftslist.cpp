/*!
 * @file aircraftslist.cpp
 *
 * @brief Custom widget implementation to represent an aircrafts list
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 09, 2015
 * @date Modified Jul 09, 2015
 */

#include "FgAircraft.h"
#include "FgControlledAircraft.h"
#include "aircraftslist.h"

#include <QLabel>

AircraftsList::AircraftsList(QWidget *parent) : QListWidget(parent)
{
    connect(this, &AircraftsList::currentItemChanged, this, &AircraftsList::itemChanged);
}

void AircraftsList::addAircraft(FgAircraft *aircraft)
{
    QListWidgetItem* item;
    item = new QListWidgetItem(this);
    item->setData(Qt::UserRole, qVariantFromValue(static_cast<void *>(aircraft)));
    QLabel* button = new QLabel(
        QString("<h3>%1</h3>%2").arg(aircraft->callsign(), "Not connected")
    );
    item->setSizeHint(button->minimumSizeHint());
    setItemWidget(item, button);

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


