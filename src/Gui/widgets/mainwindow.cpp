/*!
 * @file mainwindow.cpp
 *
 * @brief Main window implementation
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 09, 2015
 * @date Modified Jul 09, 2015
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

    connect(ui->pushButton_RunFlightgear, &QPushButton::clicked, this, &MainWindow::runFlightgear);
    connect(ui->widget_Autopilot, &AutopilotWidget::autopilotEngage, this, &MainWindow::engageAutopilot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runFlightgear()
{
    static_cast<FgControlledAircraft*>(ui->listWidget_ourAircrafts->currentAircraft())->runFlightGear();
}

void MainWindow::engageAutopilot(bool enable)
{
    static_cast<FgControlledAircraft*>(ui->listWidget_ourAircrafts->currentAircraft())->autopilot()->engage(enable);
}
