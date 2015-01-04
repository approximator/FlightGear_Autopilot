#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FgAircraft.h"
#include "FgTransport.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Transport(0)
{
    ui->setupUi(this);

    m_Transport = new FgTransport(this);

//    m_Aircrafts.append(new FgAircraft(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}
