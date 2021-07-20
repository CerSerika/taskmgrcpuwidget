#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_timer = new QTimer;
    connect(m_timer,&QTimer::timeout,this,&MainWindow::onTimerTimeOut);
    m_timer->start(1000);

    m_querythread = new CpuUsageQueryHelper();
    m_querythread->start();
}



MainWindow::~MainWindow()
{
    if(m_timer)
    {
        m_timer->stop();
        m_timer->deleteLater();
    }
    if(m_querythread)
    {
        m_querythread->StopQuery();
        m_querythread->deleteLater();
    }
    delete ui;
}

void MainWindow::onTimerTimeOut()
{
    ui->cpuwidget->AddUsageData(m_querythread->GetCpuUsage());
}
