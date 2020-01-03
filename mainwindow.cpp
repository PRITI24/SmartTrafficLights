#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->crossroadI, SIGNAL(clicked()), this, SLOT(crossroadI()));
    connect(ui->crossroadTa, SIGNAL(clicked()), this, SLOT(crossroadTa()));
    connect(ui->crossroadTb, SIGNAL(clicked()), this, SLOT(crossroadTb()));
    connect(ui->crossroadTc, SIGNAL(clicked()), this, SLOT(crossroadTc()));
    connect(ui->crossroadXa, SIGNAL(clicked()), this, SLOT(crossroadXa()));
    connect(ui->crossroadXb, SIGNAL(clicked()), this, SLOT(crossroadXb()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::crossroadI()
{
    m_i = new CrossroadI;
    m_i->setAttribute(Qt::WA_DeleteOnClose);
    m_i->show();
    this->close();
}

void MainWindow::crossroadTa()
{
    m_ta = new CrossroadTa;
    m_ta->setAttribute(Qt::WA_DeleteOnClose);
    m_ta->show();
    this->close();
}

void MainWindow::crossroadTb()
{
//    qDebug() << " crossroadTb ";
    m_tb = new CrossroadTb;
    m_tb->setAttribute(Qt::WA_DeleteOnClose);
    m_tb->show();
    this->close();
}

void MainWindow::crossroadTc()
{
    qDebug() << " crossroadTc ";
}

void MainWindow::crossroadXa()
{
    qDebug() << " crossroadXa ";
}

void MainWindow::crossroadXb()
{
    qDebug() << " crossroadXb ";
}
