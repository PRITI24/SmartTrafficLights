#include "crossroadtc.hpp"
#include "ui_crossroadtc.h"

CrossroadTc::CrossroadTc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CrossroadTc)
{
    ui->setupUi(this);

    setupSemaphores();
    setupColumns();
    setupTimeout();
    setupSemaphoreTimer();

    ui->startSimulation->raise();
    ui->buttonC1->raise();
    ui->buttonC2->raise();
    ui->buttonC3->raise();
}

CrossroadTc::~CrossroadTc()
{
    delete ui;
}

void CrossroadTc::increaseSmart()
{
    _smartTotal++;
    ui->totalCarsSmart->setText(QString::number(_smartTotal));
}

void CrossroadTc::increaseConv()
{
    _convTotal++;
    ui->totalCarsConv->setText(QString::number(_convTotal));
}

void CrossroadTc::setupSemaphores()
{
    // Changing orientation of semaphores, where neccessary
    ui->semS_3_1->setDirection(Orientation::LEFT1);
    ui->semC_3_1->setDirection(Orientation::LEFT1);

    // Semaphore 1 in description of crossroad, both smart and conv
    ui->semS_1_1->setState(State::GREEN);
    ui->semC_1_1->setState(State::GREEN);

    // Semaphore 2 in description of crossroad, both smart and conv
    ui->semS_2_1->setState(State::RED);
    ui->semC_2_1->setState(State::RED);

    // Semaphore 3 in description of crossroad, both smart and conv
    ui->semS_3_1->setState(State::RED);
    ui->semC_3_1->setState(State::RED);
}

void CrossroadTc::setupColumns()
{
    // Columns in SMART part of ui
    _s1_1 = new Column(this, 9, Direction::DOWN, 65, 55, 40, 15);
    _s1_1->attachSemaphore(ui->semS_1_1);
    _s1_1->setArrivalSensorPlace(4);
    connect(_s1_1, &Column::increaseTotalCars, this, &CrossroadTc::increaseSmart);

    _s2_1 = new Column(this, 9, Direction::UP, 155, 460, 40, 15);
    _s2_1->attachSemaphore(ui->semS_2_1);
    _s2_1->setArrivalSensorPlace(4);
    connect(_s2_1, &Column::increaseTotalCars, this, &CrossroadTc::increaseSmart);

    _s3_1 = new Column(this, 14, Direction::RIGHT, 420, 220, 15, 25);
    _s3_1->attachSemaphore(ui->semS_3_1);
    _s3_1->setArrivalSensorPlace(4);
    connect(_s3_1, &Column::increaseTotalCars, this, &CrossroadTc::increaseSmart);

    // Columns in CONV part of ui
    _c1_1 = new Column(this, 9, Direction::DOWN, 525, 55, 40, 15);
    _c1_1->attachSemaphore(ui->semC_1_1);
    _c1_1->setArrivalSensorPlace(4);
    connect(_c1_1, &Column::increaseTotalCars, this, &CrossroadTc::increaseConv);

    _c2_1 = new Column(this, 9, Direction::UP, 615, 460, 40, 15);
    _c2_1->attachSemaphore(ui->semC_2_1);
    _c2_1->setArrivalSensorPlace(4);
    connect(_c2_1, &Column::increaseTotalCars, this, &CrossroadTc::increaseConv);

    _c3_1 = new Column(this, 14, Direction::RIGHT, 880, 220, 15, 25);
    _c3_1->attachSemaphore(ui->semC_3_1);
    _c3_1->setArrivalSensorPlace(4);
    connect(_c3_1, &Column::increaseTotalCars, this, &CrossroadTc::increaseConv);
}

void CrossroadTc::setupTimeout()
{
    _timeoutClock.setParent(this);
    _timeoutClock.setInterval(TIMEOUT);

    connect(&_timeoutClock, &QTimer::timeout, _s1_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s2_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s3_1, &Column::columnTimeout);

    connect(&_timeoutClock, &QTimer::timeout, _c1_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c2_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c3_1, &Column::columnTimeout);
}

void CrossroadTc::setupSemaphoreTimer()
{
    _semaphoreClockConv.setInterval(SEMAPHORE1_TC);
    connect(&_semaphoreClockConv, &QTimer::timeout, this, &CrossroadTc::convTimeout);

    _semaphoreClockSmart.setInterval(SEMAPHORE1_TC);
    connect(&_semaphoreClockSmart, &QTimer::timeout, this, &CrossroadTc::smartTimeout);

    _semaphoreClockConv.start();
    _semaphoreClockSmart.start();
}

void CrossroadTc::convTimeout()
{
    /* Green light is over on semaphore convIt. Timer is stopped.
     * We turn red light on convIt semaphore, and turn the green light
     * on next semaphore in queue (that will be convIt+1). We increase convIt
     * and set new interval. At the end, we start timer again.
     */
    _semaphoreClockConv.stop();

    if(convIt == 1) {
        ui->semC_1_1->changeState();
        convIt = 2;
        ui->semC_2_1->changeState();
        _semaphoreClockConv.setInterval(SEMAPHORE2_TC);
    }
    else if(convIt == 2) {
        ui->semC_2_1->changeState();
        convIt = 3;
        ui->semC_3_1->changeState();
        _semaphoreClockConv.setInterval(SEMAPHORE3_TC);
    }
    else if(convIt == 3) {
        ui->semC_3_1->changeState();
        convIt = 1;
        ui->semC_1_1->changeState();
        _semaphoreClockConv.setInterval(SEMAPHORE1_TC);
    }
    _semaphoreClockConv.start();
}

void CrossroadTc::smartTimeout()
{
    /* This smartTimeout() is almost the same like previous.
     * Major difference is that at each timeout, we must check
     * does fuzzybrain says we must extend green light at current
     * semaphore or no.
     */
    _semaphoreClockSmart.stop();

    if(smartIt == 1) {
        if(previouslyExtended == false) {
            float ext1 = fuzzyBrain(_s1_1->queueLength(), _s1_1->arrivalRate());
            int extension = qCeil(double(ext1)/3);
            _semaphoreClockSmart.setInterval(extension);
            previouslyExtended = true;
        }
        else {
            ui->semS_1_1->changeState();
            smartIt = 2;
            ui->semS_2_1->changeState();
            _semaphoreClockSmart.setInterval(SEMAPHORE2_TC);
            previouslyExtended = false;
        }
    }

    else if(smartIt == 2) {
        if(previouslyExtended == false) {
            float ext1 = fuzzyBrain(_s2_1->queueLength(), _s2_1->arrivalRate());
            int extension = qCeil(double(ext1)/2);
            _semaphoreClockSmart.setInterval(extension);
            previouslyExtended = true;
        }
        else {
            ui->semS_2_1->changeState();
            smartIt = 3;
            ui->semS_3_1->changeState();
            _semaphoreClockSmart.setInterval(SEMAPHORE3_TC);
            previouslyExtended = false;
        }
    }

    else if (smartIt == 3 ) {
        if(previouslyExtended == false) {
            float ext1 = fuzzyBrain(_s3_1->queueLength(), _s3_1->arrivalRate());
            int extension = qCeil(double(ext1));
            _semaphoreClockSmart.setInterval(extension);
            previouslyExtended = true;
        }
        else {
            ui->semS_3_1->changeState();
            smartIt = 1;
            ui->semS_1_1->changeState();
            _semaphoreClockSmart.setInterval(SEMAPHORE1_TC);
            previouslyExtended = false;
        }
    }
    _semaphoreClockSmart.start();
}

void CrossroadTc::on_startSimulation_clicked()
{
    ui->startSimulation->setEnabled(false);
    _timeoutClock.start();
}

void CrossroadTc::on_buttonC1_clicked()
{
    _s1_1->scheduleCar();
    _c1_1->scheduleCar();
}


void CrossroadTc::on_buttonC2_clicked()
{
    _s2_1->scheduleCar();
    _c2_1->scheduleCar();
}

void CrossroadTc::on_buttonC3_clicked()
{
    _s3_1->scheduleCar();
    _c3_1->scheduleCar();
}

float CrossroadTc::fuzzyBrain(int queueLength, int arrivalRate)
{
    // FOR NOW JUST COPY THIS METHOD EVERYWHERE, SETUP FUZZY SYSTEM LATER !!!!

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

    return result * MULTIPLIER_TC;
}

void CrossroadTc::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
        ui->buttonC1->click();
    if(event->key() == Qt::Key_S)
        ui->buttonC2->click();
    if(event->key() == Qt::Key_D)
        ui->buttonC3->click();
}
