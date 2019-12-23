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
    qDebug() << " crossroadI ";
}

void MainWindow::crossroadTa()
{
    qDebug() << " crossroadTa ";
}

void MainWindow::crossroadTb()
{
    qDebug() << " crossroadTb ";
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
