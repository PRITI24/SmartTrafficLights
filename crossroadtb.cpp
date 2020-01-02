#include "crossroadtb.hpp"
#include "ui_crossroadtb.h"

CrossroadTb::CrossroadTb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CrossroadTb)
{
    ui->setupUi(this);
}

CrossroadTb::~CrossroadTb()
{
    delete ui;
}
