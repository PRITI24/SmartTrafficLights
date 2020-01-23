#include "crossroadta.hpp"
#include "ui_crossroadta.h"

CrossroadTa::CrossroadTa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CrossroadTa)
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
    ui->buttonC4->raise();
    ui->buttonC5->raise();
    ui->buttonC6->raise();
}

CrossroadTa::~CrossroadTa()
{
    delete ui;
}

void CrossroadTa::increaseSmart()
{
    _smartTotal++;
    ui->totalCarsSmart->setText(QString::number(_smartTotal));
}

void CrossroadTa::increaseConv()
{
    _convTotal++;
    ui->totalCarsConv->setText(QString::number(_convTotal));
}

void CrossroadTa::setupSemaphores()
{
    // Changing orientation of semaphores, where neccessary
    ui->semS_3_1->setDirection(Orientation::LEFT1);
    ui->semC_3_1->setDirection(Orientation::LEFT1);
    ui->semS_2_2->setDirection(Orientation::LEFT1);
    ui->semC_2_2->setDirection(Orientation::LEFT1);

    // Semaphore 1 in description of crossroad, both smart and conv
    ui->semS_1_1->setState(State::GREEN);
    ui->semS_1_2->setState(State::GREEN);
    ui->semS_1_3->setState(State::GREEN);
    ui->semC_1_1->setState(State::GREEN);
    ui->semC_1_2->setState(State::GREEN);
    ui->semC_1_3->setState(State::GREEN);

    // Semaphore 2 in description of crossroad, both smart and conv
    ui->semS_2_1->setState(State::RED);
    ui->semS_2_2->setState(State::RED);
    ui->semC_2_1->setState(State::RED);
    ui->semC_2_2->setState(State::RED);

    // Semaphore 3 in description of crossroad, both smart and conv
    ui->semS_3_1->setState(State::RED);
    ui->semC_3_1->setState(State::RED);
}

void CrossroadTa::setupColumns()
{
    // Columns in SMART part of ui
    _s1_1 = new Column(this, 9, Direction::DOWN, 50, 55, 40, 15);
    _s1_1->attachSemaphore(ui->semS_1_1);
    _s1_1->setArrivalSensorPlace(3);
    connect(_s1_1, &Column::increaseTotalCars, this, &CrossroadTa::increaseSmart);

    _s1_2 = new Column(this, 9, Direction::UP, 140, 460, 40, 15);
    _s1_2->attachSemaphore(ui->semS_1_2);
    _s1_2->setArrivalSensorPlace(3);
    connect(_s1_2, &Column::increaseTotalCars, this, &CrossroadTa::increaseSmart);

    _s1_3 = new Column(this, 9, Direction::UP, 185, 460, 40, 15);
    _s1_3->attachSemaphore(ui->semS_1_3);
    _s1_3->setArrivalSensorPlace(3);
    connect(_s1_3, &Column::increaseTotalCars, this, &CrossroadTa::increaseSmart);

    _s2_1 = new Column(this, 9, Direction::DOWN, 95, 55, 40, 15);
    _s2_1->attachSemaphore(ui->semS_2_1);
    _s2_1->setArrivalSensorPlace(3);
    connect(_s2_1, &Column::increaseTotalCars, this, &CrossroadTa::increaseSmart);

    _s2_2 = new Column(this, 14, Direction::RIGHT, 420, 200, 15, 25);
    _s2_2->attachSemaphore(ui->semS_2_2);
    _s2_2->setArrivalSensorPlace(4);
    connect(_s2_2, &Column::increaseTotalCars, this, &CrossroadTa::increaseSmart);

    _s3_1 = new Column(this, 14, Direction::RIGHT, 420, 235, 15, 25);
    _s3_1->attachSemaphore(ui->semS_3_1);
    _s3_1->setArrivalSensorPlace(4);
    connect(_s3_1, &Column::increaseTotalCars, this, &CrossroadTa::increaseSmart);

    // Columns in CONV part of ui
    _c1_1 = new Column(this, 9, Direction::DOWN, 510, 55, 40, 15);
    _c1_1->attachSemaphore(ui->semC_1_1);
    _c1_1->setArrivalSensorPlace(0);
    connect(_c1_1, &Column::increaseTotalCars, this, &CrossroadTa::increaseConv);

    _c1_2 = new Column(this, 9, Direction::UP, 600, 460, 40, 15);
    _c1_2->attachSemaphore(ui->semC_1_2);
    _c1_2->setArrivalSensorPlace(0);
    connect(_c1_2, &Column::increaseTotalCars, this, &CrossroadTa::increaseConv);

    _c1_3 = new Column(this, 9, Direction::UP, 645, 460, 40, 15);
    _c1_3->attachSemaphore(ui->semC_1_3);
    _c1_3->setArrivalSensorPlace(0);
    connect(_c1_3, &Column::increaseTotalCars, this, &CrossroadTa::increaseConv);

    _c2_1 = new Column(this, 9, Direction::DOWN, 555, 55, 40, 15);
    _c2_1->attachSemaphore(ui->semC_2_1);
    _c2_1->setArrivalSensorPlace(0);
    connect(_c2_1, &Column::increaseTotalCars, this, &CrossroadTa::increaseConv);

    _c2_2 = new Column(this, 14, Direction::RIGHT, 880, 200, 15, 25);
    _c2_2->attachSemaphore(ui->semC_2_2);
    _c2_2->setArrivalSensorPlace(0);
    connect(_c2_2, &Column::increaseTotalCars, this, &CrossroadTa::increaseConv);

    _c3_1 = new Column(this, 14, Direction::RIGHT, 880, 235, 15, 25);
    _c3_1->attachSemaphore(ui->semC_3_1);
    _c3_1->setArrivalSensorPlace(0);
    connect(_c3_1, &Column::increaseTotalCars, this, &CrossroadTa::increaseConv);

}

void CrossroadTa::setupTimeout()
{
    _timeoutClock.setParent(this);
    _timeoutClock.setInterval(TIMEOUT);

    connect(&_timeoutClock, &QTimer::timeout, _s1_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s1_2, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s1_3, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s2_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s2_2, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s3_1, &Column::columnTimeout);

    connect(&_timeoutClock, &QTimer::timeout, _c1_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c1_2, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c1_3, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c2_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c2_2, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c3_1, &Column::columnTimeout);

    connect(&_timeoutClock, &QTimer::timeout, this, &CrossroadTa::updateLogger);

}

void CrossroadTa::setupSemaphoreTimer()
{
    _semaphoreClockConv.setInterval(SEMAPHORE1_TA);
    connect(&_semaphoreClockConv, &QTimer::timeout, this, &CrossroadTa::convTimeout);

    _semaphoreClockSmart.setInterval(SEMAPHORE1_TA);
    connect(&_semaphoreClockSmart, &QTimer::timeout, this, &CrossroadTa::smartTimeout);

    _semaphoreClockConv.start();
    _semaphoreClockSmart.start();

}

void CrossroadTa::updateLogger()
{
    smartLogger.push_back(_smartTotal);
    convientLogger.push_back(_convTotal);
}

void CrossroadTa::convTimeout()
{
    /* Green light is over on semaphore convIt. Timer is stopped.
     * We turn red light on convIt semaphore, and turn the green light
     * on next semaphore in queue (that will be convIt+1). We increase convIt
     * and set new interval. At the end, we start timer again.
     */
    _semaphoreClockConv.stop();

    if(convIt == 1) {
        ui->semC_1_1->changeState();
        ui->semC_1_2->changeState();
        ui->semC_1_3->changeState();
        ui->semC_2_1->changeState();
        ui->semC_2_2->changeState();
        _semaphoreClockConv.setInterval(SEMAPHORE2_TA);
        convIt = 2;
    }
    else if(convIt == 2) {
        ui->semC_2_1->changeState();
        ui->semC_2_2->changeState();
        ui->semC_3_1->changeState();
        _semaphoreClockConv.setInterval(SEMAPHORE3_TA);
        convIt = 3;
    }
    else if(convIt == 3) {
        ui->semC_3_1->changeState();
        ui->semC_1_1->changeState();
        ui->semC_1_2->changeState();
        ui->semC_1_3->changeState();
        _semaphoreClockConv.setInterval(SEMAPHORE1_TA);
        convIt = 1;
    }
    _semaphoreClockConv.start();
}

void CrossroadTa::smartTimeout()
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
            float ext2 = fuzzyBrain(_s1_2->queueLength(), _s1_2->arrivalRate());
            float ext3 = fuzzyBrain(_s1_3->queueLength(), _s1_3->arrivalRate());
            int extension = qCeil(double(ext1 + ext2 + ext3)/3);
            qDebug() << "Extension 1 : " << QString::number(double(extension));
            _semaphoreClockSmart.setInterval(extension);
            previouslyExtended = true;
        }
        else {
            ui->semS_1_1->changeState();
            ui->semS_1_2->changeState();
            ui->semS_1_3->changeState();
            smartIt = 2;
            ui->semS_2_1->changeState();
            ui->semS_2_2->changeState();
            _semaphoreClockSmart.setInterval(SEMAPHORE2_TA);
            previouslyExtended = false;
        }
    }

    else if(smartIt == 2) {
        if(previouslyExtended == false) {
            float ext1 = fuzzyBrain(_s2_1->queueLength(), _s2_1->arrivalRate());
            float ext2 = fuzzyBrain(_s2_2->queueLength(), _s2_2->arrivalRate());
            int extension = qCeil(double(ext1 + ext2)/2);
            qDebug() << "Extension 2 : " << QString::number(double(extension));
            _semaphoreClockSmart.setInterval(extension);
            previouslyExtended = true;
        }
        else {
            ui->semS_2_1->changeState();
            ui->semS_2_2->changeState();
            smartIt = 3;
            ui->semS_3_1->changeState();
            _semaphoreClockSmart.setInterval(SEMAPHORE3_TA);
            previouslyExtended = false;
        }
    }

    else if (smartIt == 3 ) {
        if(previouslyExtended == false) {
            float ext1 = fuzzyBrain(_s3_1->queueLength(), _s3_1->arrivalRate());
            int extension = qCeil(double(ext1));
            _semaphoreClockSmart.setInterval(extension);
            qDebug() << "Extension 3 : " << QString::number(double(extension));
            previouslyExtended = true;
        }
        else {
            ui->semS_3_1->changeState();
            smartIt = 1;
            ui->semS_1_1->changeState();
            ui->semS_1_2->changeState();
            ui->semS_1_3->changeState();
            _semaphoreClockSmart.setInterval(SEMAPHORE1_TA);
            previouslyExtended = false;
        }
    }
    _semaphoreClockSmart.start();
}

void CrossroadTa::on_startSimulation_clicked()
{
    ui->startSimulation->setEnabled(false);
    _timeoutClock.start();
}

void CrossroadTa::on_buttonC1_clicked()
{
    if(_s1_1->columnFull() || _c1_1->columnFull())
        return;
    _s1_1->scheduleCar();
    _c1_1->scheduleCar();
}

void CrossroadTa::on_buttonC3_clicked()
{
    if(!(_s1_2->columnFull() || _c1_2->columnFull())) {
        _s1_2->scheduleCar();
        _c1_2->scheduleCar();
    }
}

void CrossroadTa::on_buttonC4_clicked()
{
    if(!(_s1_3->columnFull() || _c1_3->columnFull())) {
        _s1_3->scheduleCar();
        _c1_3->scheduleCar();
    }
}

void CrossroadTa::on_buttonC2_clicked()
{
    if(!(_s2_1->columnFull() || _c2_1->columnFull())) {
        _s2_1->scheduleCar();
        _c2_1->scheduleCar();
    }
}

void CrossroadTa::on_buttonC5_clicked()
{
    if(!(_s2_2->columnFull() || _c2_2->columnFull())) {
        _s2_2->scheduleCar();
        _c2_2->scheduleCar();
    }
}

void CrossroadTa::on_buttonC6_clicked()
{
    if(!(_s3_1->columnFull() || _c3_1->columnFull())) {
        _s3_1->scheduleCar();
        _c3_1->scheduleCar();
    }
}

float CrossroadTa::fuzzyBrain(int queueLength, int arrivalRate)
{
    _controller1 = new FuzzyController();

    _controller1->addInput(new FuzzyInput("Queue"));
    _controller1->is("Queue")->appendVariable(new FuzzyInputVariable("vshort", QVector<float>{1,2}, QVector<float>{1,0}, queueLength));
    _controller1->is("Queue")->appendVariable(new FuzzyInputVariable("short", QVector<float>{1,2,3,4}, QVector<float>{0,1,1,0}, queueLength));
    _controller1->is("Queue")->appendVariable(new FuzzyInputVariable("middle", QVector<float>{2,4,5,7}, QVector<float>{0,1,1,0}, queueLength));
    _controller1->is("Queue")->appendVariable(new FuzzyInputVariable("long", QVector<float>{5,6,7,8}, QVector<float>{0,1,1,0}, queueLength));
    _controller1->is("Queue")->appendVariable(new FuzzyInputVariable("vlong", QVector<float>{7,8}, QVector<float>{0,1}, queueLength));

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

    result < 0 ? result = 0 : result;

    return result * MULTIPLIER_TA;
}

void CrossroadTa::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
        ui->buttonC1->click();
    if(event->key() == Qt::Key_S)
        ui->buttonC2->click();
    if(event->key() == Qt::Key_D)
        ui->buttonC3->click();
    if(event->key() == Qt::Key_F)
        ui->buttonC4->click();
    if(event->key() == Qt::Key_I)
        ui->buttonC5->click();
    if(event->key() == Qt::Key_K)
        ui->buttonC6->click();

    if(event->key() == Qt::Key_Z) {
        _timeoutClock.stop();
        dataLogger = new DataLogger(nullptr, smartLogger, convientLogger);
        dataLogger->setAttribute(Qt::WA_DeleteOnClose);
        dataLogger->show();
        this->close();
    }if(event->key() == Qt::Key_Z) {
        _timeoutClock.stop();
        dataLogger = new DataLogger(nullptr, smartLogger, convientLogger);
        dataLogger->setAttribute(Qt::WA_DeleteOnClose);
        dataLogger->show();
        this->close();
    }
}
