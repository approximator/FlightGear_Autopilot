#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

namespace Ui {
class MainWindow;
}

class FgAircraft;
class FgTransport;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    FgTransport *m_Transport;

    QList<FgAircraft *> m_Aircrafts;
    QList<FgAircraft *> m_OtherPilots;

private slots:
    void onDataUpdated();
    void on_actionWriteProtocol_triggered();
};

#endif // MAINWINDOW_H
