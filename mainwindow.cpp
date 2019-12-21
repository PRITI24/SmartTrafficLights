#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Test::FuzzyControlerTDD();
}

MainWindow::~MainWindow()
{
    delete ui;
}

