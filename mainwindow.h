#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cpuusagequeryhelper.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void onTimerTimeOut();

private:
    Ui::MainWindow *ui;

    QTimer* m_timer;

    CpuUsageQueryHelper* m_querythread;
};

#endif // MAINWINDOW_H
 
