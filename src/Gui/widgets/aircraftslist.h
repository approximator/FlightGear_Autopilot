/*!
 * @file aircraftslist.h
 *
 * @brief Custom widget to represent an aircrafts list
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 09, 2015
 * @date Modified Jul 09, 2015
 */

#ifndef AIRCRAFTSLIST_H
#define AIRCRAFTSLIST_H

#include <QListWidget>

class FgAircraft;

class AircraftsList : public QListWidget
{
    Q_OBJECT
public:
    AircraftsList(QWidget *parent = 0);
    FgAircraft* currentAircraft();

signals:
    void aircraftSelected(FgAircraft *aircraft);

private slots:
    void itemChanged(QListWidgetItem* current, QListWidgetItem* previous);

public slots:
    void addAircraft(FgAircraft *aircraft);
    void updateAircraft(FgAircraft *aircraft);
    void removeAircraft(FgAircraft *aircraft);
};

#endif // AIRCRAFTSLIST_H
