/*!
 * @file mainwindow.h
 *
 * @brief Main window
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 09, 2015
 * @date Modified Jul 20, 2015
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FgAircraftsModel.h"
#include "aircraftslist.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(const MainWindow& other);
    MainWindow& operator=(const MainWindow& other);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    FgAircraftsModel fgapModel { };

private slots:
    void engageAutopilot(bool enable);
    void updateView(const QModelIndex &index);
};

#endif // MAINWINDOW_H
