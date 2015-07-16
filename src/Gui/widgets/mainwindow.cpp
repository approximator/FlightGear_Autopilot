/*!
 * @file mainwindow.cpp
 *
 * @brief Main window implementation
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 09, 2015
 * @date Modified Jul 16, 2015
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&controller, &FgController::ourAircraftAdded, ui->listWidget_ourAircrafts, &AircraftsList::addAircraft);
    controller.init();
    connect(ui->widget_Autopilot, &AutopilotWidget::autopilotEngage, this, &MainWindow::engageAutopilot);
    connect(ui->listWidget_ourAircrafts, &AircraftsList::aircraftSelected, this, &MainWindow::updateView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::engageAutopilot(bool enable)
{
    FgControlledAircraft* aircraft = static_cast<FgControlledAircraft*>(ui->listWidget_ourAircrafts->currentAircraft());
    aircraft->autopilot()->engage(enable);
}

void MainWindow::updateView()
{
    FgControlledAircraft* aircraft = static_cast<FgControlledAircraft*>(ui->listWidget_ourAircrafts->currentAircraft());
    ui->label_Callsign->setText(aircraft->callsign());
}
