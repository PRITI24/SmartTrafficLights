#include "crossroadi.hpp"
#include "ui_crossroadi.h"

CrossroadI::CrossroadI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CrossroadI)
{
    ui->setupUi(this);

    setupSemaphores();
    setupColumns();
    setupTimeout();
    setupSemaphoreTimers();

    // Start simulation button
    startSimButton = new QPushButton("Start simulator", this);
    startSimButton->setGeometry(10,10,95,20);
    connect(startSimButton, &QPushButton::clicked, this, &CrossroadI::onstartSimButtonClicked);
    startSimButton->show();
    //

    // Add car for _Scolumn1 button
    addSColumn1Button = new QPushButton("Add", this);
    addSColumn1Button->setGeometry(85,40,90,20);
    connect(addSColumn1Button, &QPushButton::clicked, this, &CrossroadI::scheduledCarForSColumn1);
    connect(addSColumn1Button, &QPushButton::clicked, this, &CrossroadI::scheduledCarForCColumn1);
    addSColumn1Button->show();
    //

    // Add car for _Scolumn2 button
    addSColumn2Button = new QPushButton("Add", this);
    addSColumn2Button->setGeometry(210,600,90,20);
    connect(addSColumn2Button, &QPushButton::clicked, this, &CrossroadI::scheduledCarForSColumn2);
    connect(addSColumn2Button, &QPushButton::clicked, this, &CrossroadI::scheduledCarForCColumn2);
    addSColumn1Button->show();
    //

}

CrossroadI::~CrossroadI()
{
    delete ui;
}

void CrossroadI::onstartSimButtonClicked()
{
    startSimButton->setEnabled(false);
    timeoutClock.start();
}

void CrossroadI::scheduledCarForSColumn1()
{
    _Scolumn1->scheduleCar();
}

void CrossroadI::scheduledCarForSColumn2()
{
    _Scolumn2->scheduleCar();
}

void CrossroadI::scheduledCarForCColumn1()
{
    _Ccolumn1->scheduleCar();
}

void CrossroadI::scheduledCarForCColumn2()
{
    _Ccolumn2->scheduleCar();
}

void CrossroadI::s1Timeout()
{

    _s1Timer.stop();
    if((ui->_Ssemaphore1->state() == State::GREEN) && (previouslyExtended == false)) {
        float extension1 = fuzzyBrain(_Scolumn1->queueLength(), _Scolumn1->arrivalRate());
        float extension2 = fuzzyBrain(_Scolumn2->queueLength(), _Scolumn2->arrivalRate());
        int e = qCeil(double(extension1 + extension2)/2);
        previouslyExtended = true;
        qDebug() << " SEMAPHORE 1 EXTENDED FOR:" << QString::number(e);
        _s1Timer.setInterval(e);
        _s1Timer.start();
        return;
    }

    else if((ui->_Ssemaphore1->state() == State::GREEN)) {
       _s1Timer.setInterval(REDLIGHT);
    }
    else {
        _s1Timer.setInterval(GREENLIGHT);
    }

    previouslyExtended = false;
    ui->_Ssemaphore1->changeState();
    ui->_Ssemaphore2->changeState();
    _s1Timer.start();

}

void CrossroadI::c1Timeout(){
    _c1Timer.stop();
    if(ui->_Csemaphore1->state() == State::GREEN) {
        _c1Timer.setInterval(REDLIGHT);
    }
    else {
        _c1Timer.setInterval(GREENLIGHT);
    }

    ui->_Csemaphore1->changeState();
    ui->_Csemaphore2->changeState();
    _c1Timer.start();
}

void CrossroadI::increaseTotalS()
{
    _totalCarsSmart++;
    ui->totalCarsSmart->setText(QString::number(_totalCarsSmart));
}

void CrossroadI::increaseTotalC()
{
    _totalCarsConv++;
    ui->totalCarsConv->setText(QString::number(_totalCarsConv/2));
}

void CrossroadI::setupSemaphores()
{
    ui->_Ssemaphore1->setState(State::RED);
    ui->_Ssemaphore2->setState(State::RED);
    ui->_Csemaphore1->setState(State::RED);
    ui->_Csemaphore2->setState(State::RED);
}

void CrossroadI::setupColumns()
{
    _Scolumn1 = new Column(this, 12, Direction::DOWN, 80, 60, 100, 20);
    _Scolumn1->attachSemaphore(ui->_Ssemaphore1);
    _Scolumn1->setArrivalSensorPlace(5);
    _Scolumn2 = new Column(this, 12, Direction::UP, 200, 580, 100, 20);
    _Scolumn2->attachSemaphore(ui->_Ssemaphore2);
    _Scolumn2->setArrivalSensorPlace(5);
    connect(_Scolumn1, &Column::increaseTotalCars, this, &CrossroadI::increaseTotalS);
    connect(_Scolumn2, &Column::increaseTotalCars, this, &CrossroadI::increaseTotalS);

    _Ccolumn1 = new Column(this, 12, Direction::DOWN, 500, 60, 100, 20);
    _Ccolumn1->attachSemaphore(ui->_Csemaphore1);
    _Ccolumn2 = new Column(this, 12, Direction::UP, 620, 580, 100, 20);
    _Ccolumn2->attachSemaphore(ui->_Csemaphore2);
    connect(_Ccolumn1, &Column::increaseTotalCars, this, &CrossroadI::increaseTotalC);
    connect(_Ccolumn1, &Column::increaseTotalCars, this, &CrossroadI::increaseTotalC);
}

void CrossroadI::setupTimeout()
{
    timeoutClock.setParent(this);
    timeoutClock.setInterval(TIMEOUT);
    connect(&timeoutClock, &QTimer::timeout, _Scolumn1, &Column::columnTimeout);
    connect(&timeoutClock, &QTimer::timeout, _Scolumn2, &Column::columnTimeout);
    connect(&timeoutClock, &QTimer::timeout, _Ccolumn1, &Column::columnTimeout);
    connect(&timeoutClock, &QTimer::timeout, _Ccolumn2, &Column::columnTimeout);
}

void CrossroadI::setupSemaphoreTimers()
{
    _c1Timer.setInterval(REDLIGHT);
    connect(&_c1Timer, &QTimer::timeout, this, &CrossroadI::c1Timeout);

    _s1Timer.setInterval(REDLIGHT);
    connect(&_s1Timer, &QTimer::timeout, this, &CrossroadI::s1Timeout);

    _c1Timer.start();
    _s1Timer.start();
}

float CrossroadI::fuzzyBrain(int queueLength, int arrivalRate)
{
    _controller1 = new FuzzyController();

    _controller1->addInput(new FuzzyInput("Queue"));
    _controller1->is("Queue")->appendVariable(new FuzzyInputVariable("vshort", QVector<float>{0,2}, QVector<float>{1,0}, queueLength));
    _controller1->is("Queue")->appendVariable(new FuzzyInputVariable("short", QVector<float>{1,2,4,5}, QVector<float>{0,1,1,0}, queueLength));
    _controller1->is("Queue")->appendVariable(new FuzzyInputVariable("middle", QVector<float>{4,6,8}, QVector<float>{0,1,0}, queueLength));
    _controller1->is("Queue")->appendVariable(new FuzzyInputVariable("long", QVector<float>{7,8,10,11}, QVector<float>{0,1,1,0}, queueLength));
    _controller1->is("Queue")->appendVariable(new FuzzyInputVariable("vlong", QVector<float>{10,12}, QVector<float>{0,1}, queueLength));

    _controller1->addInput(new FuzzyInput("Arrival"));
    _controller1->is("Arrival")->appendVariable(new FuzzyInputVariable("small", QVector<float>{0,2}, QVector<float>{1,0}, arrivalRate));
    _controller1->is("Arrival")->appendVariable(new FuzzyInputVariable("average", QVector<float>{1,3,5}, QVector<float>{0,1,0}, arrivalRate));
    _controller1->is("Arrival")->appendVariable(new FuzzyInputVariable("big", QVector<float>{4,6}, QVector<float>{0,1}, arrivalRate));

    _controller1->addOutput(new FuzzyOutput("Extension"));
    _controller1->is("Extension",0)->appendVariable(new FuzzyOutputVariable("vsmall", QVector<float>{0,10}, QVector<float>{1,0}));
    _controller1->is("Extension",0)->appendVariable(new FuzzyOutputVariable("small", QVector<float>{0,5,10,15}, QVector<float>{0,1,1,0}));
    _controller1->is("Extension",0)->appendVariable(new FuzzyOutputVariable("big", QVector<float>{10,15,20,25}, QVector<float>{0,1,1,0}));
    _controller1->is("Extension",0)->appendVariable(new FuzzyOutputVariable("vbig", QVector<float>{15,25}, QVector<float>{0,1}));

    _controller1->addRule(_controller1->is("Extension",0)->is("vbig"), _controller1->is("Queue")->is("vlong"));

    _controller1->addRule(_controller1->is("Extension",0)->is("vbig"), _controller1->is("Queue")->is("long"), _controller1->is("Arrival")->is("big"), Logic::AND);
    _controller1->addRule(_controller1->is("Extension",0)->is("big"), _controller1->is("Queue")->is("long"), _controller1->is("Arrival")->is("average"), Logic::AND);
    _controller1->addRule(_controller1->is("Extension",0)->is("small"), _controller1->is("Queue")->is("long"), _controller1->is("Arrival")->is("small"), Logic::AND);

    _controller1->addRule(_controller1->is("Extension",0)->is("big"), _controller1->is("Queue")->is("middle"), _controller1->is("Arrival")->is("big"), Logic::AND);
    _controller1->addRule(_controller1->is("Extension",0)->is("small"), _controller1->is("Queue")->is("middle"), _controller1->is("Arrival")->is("average"), Logic::AND);
    _controller1->addRule(_controller1->is("Extension",0)->is("vsmall"), _controller1->is("Queue")->is("middle"), _controller1->is("Arrival")->is("small"), Logic::AND);


    _controller1->addRule(_controller1->is("Extension",0)->is("small"), _controller1->is("Queue")->is("short"), _controller1->is("Arrival")->is("big"), Logic::AND);
    _controller1->addRule(_controller1->is("Extension",0)->is("vsmall"), _controller1->is("Queue")->is("short"), _controller1->is("Arrival")->is("average"), Logic::AND);
    _controller1->addRule(_controller1->is("Extension",0)->is("vsmall"), _controller1->is("Queue")->is("short"), _controller1->is("Arrival")->is("small"), Logic::AND);

    _controller1->addRule(_controller1->is("Extension",0)->is("vsmall"), _controller1->is("Queue")->is("vshort"));

    float result = qCeil(double(_controller1->solve()));

    //qDebug() << "fuzzybrain:" << QString::number(result);

    return result * MULTIPLIER;
}
