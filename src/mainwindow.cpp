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
    ui->menuBar->setVisible(false);

    m_Transport = new FgTransport(this);
    connect(m_Transport, SIGNAL(dataUpdated()), this, SLOT(onDataUpdated()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDataUpdated()
{
    //! @todo Do not do this on each update. Track changes only.
    ui->listWidget_otherPilots->clear();
    int otherPilots = m_Transport->getInt("/ai/models/num-players");
    for (int i = 0; i < otherPilots; ++i)
    {
        ui->listWidget_otherPilots->addItem(m_Transport->getString("/ai/models/multiplayer[" + QString::number(i) + "]/callsign"));
    }
}

void MainWindow::on_actionWriteProtocol_triggered()
{
    qDebug() << "Write protocol";
    m_Transport->protocol()->writeXml(ui->lineEdit_fgPath->text());
}

