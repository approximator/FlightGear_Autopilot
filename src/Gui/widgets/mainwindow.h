/*!
 * @file mainwindow.h
 *
 * @brief Main window
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 09, 2015
 * @date Modified Jul 16, 2015
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FgController.h"
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

    FgController controller { };

private slots:
    void engageAutopilot(bool enable);
    void updateView();
};

#endif // MAINWINDOW_H
