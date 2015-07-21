/*!
 * @file mainwindow.cpp
 *
 * @brief Main window implementation
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 09, 2015
 * @date Modified Jul 20, 2015
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listView_ourAircrafts->setModel(&fgapModel);
    fgapModel.init();
    connect(ui->widget_Autopilot, &AutopilotWidget::autopilotEngage, this, &MainWindow::engageAutopilot);
    connect(ui->listView_ourAircrafts, &QListView::activated, this, &MainWindow::updateView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::engageAutopilot(bool enable)
{
    Q_UNUSED(enable);
//    FgControlledAircraft* aircraft = static_cast<FgControlledAircraft*>(ui->listWidget_ourAircrafts->currentAircraft());
//    aircraft->autopilot()->engage(enable);
}

void MainWindow::updateView(const QModelIndex &index)
{
    ui->label_Callsign->setText(fgapModel.data(index).toString());
}
