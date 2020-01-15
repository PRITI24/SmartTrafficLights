#include "crossroadxa.hpp"
#include "ui_crossroadxa.h"

CrossroadXa::CrossroadXa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CrossroadXa)
{
    ui->setupUi(this);

    setupSemaphores();
    setupColumns();
    setupTimeout();
    setupSemaphoreTimer();

    ui->totalCarsConv->setDisabled(true);
    ui->totalCarsSmart->setDisabled(true);

    ui->startSimulation->raise();
    ui->buttonC1->raise();
    ui->buttonC2->raise();
    ui->buttonC3->raise();
    ui->buttonC4->raise();
    ui->buttonC5->raise();
    ui->buttonC6->raise();
    ui->buttonC7->raise();
    ui->buttonC8->raise();
}

CrossroadXa::~CrossroadXa()
{
    delete ui;
}

void CrossroadXa::increaseSmart()
{
    _smartTotal++;
    ui->totalCarsSmart->setText(QString::number(_smartTotal));
}

void CrossroadXa::increaseConv()
{
    _convTotal++;
    ui->totalCarsConv->setText(QString::number(_convTotal));
}

void CrossroadXa::on_startSimulation_clicked()
{
    ui->startSimulation->setEnabled(false);
    _timeoutClock.start();
}

void CrossroadXa::on_buttonC1_clicked()
{
    if(_s1_1->columnFull() || _c1_1->columnFull())
        return;
    _s1_1->scheduleCar();
    _c1_1->scheduleCar();
}

void CrossroadXa::on_buttonC2_clicked()
{
    if(_s3_1->columnFull() || _c3_1->columnFull())
        return;
    _s3_1->scheduleCar();
    _c3_1->scheduleCar();
}

void CrossroadXa::on_buttonC3_clicked()
{
    if(_s2_1->columnFull() || _c2_1->columnFull())
        return;
    _s2_1->scheduleCar();
    _c2_1->scheduleCar();
}

void CrossroadXa::on_buttonC4_clicked()
{
    if(_s4_1->columnFull() || _c4_1->columnFull())
        return;
    _s4_1->scheduleCar();
    _c4_1->scheduleCar();
}

void CrossroadXa::on_buttonC5_clicked()
{
    if(_s1_2->columnFull() || _c1_2->columnFull())
        return;
    _s1_2->scheduleCar();
    _c1_2->scheduleCar();
}

void CrossroadXa::on_buttonC6_clicked()
{
    if(_s3_2->columnFull() || _c3_2->columnFull())
        return;
    _s3_2->scheduleCar();
    _c3_2->scheduleCar();
}

void CrossroadXa::on_buttonC7_clicked()
{
    if(_s2_2->columnFull() || _c2_2->columnFull())
        return;
    _s2_2->scheduleCar();
    _c2_2->scheduleCar();
}

void CrossroadXa::on_buttonC8_clicked()
{
    if(_s4_2->columnFull() || _c4_2->columnFull())
        return;
    _s4_2->scheduleCar();
    _c4_2->scheduleCar();
}

void CrossroadXa::convTimeout()
{
    _semaphoreClockConv.stop();

     if(convIt == 1) {
         ui->semC_1_1->changeState();
         ui->semC_1_2->changeState();
         ui->semC_2_1->changeState();
         ui->semC_2_2->changeState();
         _semaphoreClockConv.setInterval(SEMAPHORE2_XA);
         convIt = 2;
     }
     else if(convIt == 2) {
         ui->semC_2_1->changeState();
         ui->semC_2_2->changeState();
         ui->semC_3_1->changeState();
         ui->semC_3_2->changeState();
         _semaphoreClockConv.setInterval(SEMAPHORE3_XA);
         convIt = 3;
     }
     else if(convIt == 3) {
         ui->semC_3_1->changeState();
         ui->semC_3_2->changeState();
         ui->semC_4_1->changeState();
         ui->semC_4_2->changeState();
         _semaphoreClockConv.setInterval(SEMAPHORE4_XA);
         convIt = 4;
     }
     else if(convIt == 4) {
         ui->semC_4_1->changeState();
         ui->semC_4_2->changeState();
         ui->semC_1_1->changeState();
         ui->semC_1_2->changeState();
         _semaphoreClockConv.setInterval(SEMAPHORE1_XA);
         convIt = 1;
     }
     _semaphoreClockConv.start();
}

void CrossroadXa::smartTimeout()
{
    _semaphoreClockSmart.stop();

    if(smartIt == 1) {
        if(previouslyExtended == false) {
            float ext1 = fuzzyBrain(_s1_1->queueLength(), _s1_1->arrivalRate());
            float ext2 = fuzzyBrain(_s1_2->queueLength(), _s1_2->arrivalRate());
            int extension = qCeil(double(ext1 + ext2)/2);
            qDebug() << "Extension 1 : " << QString::number(double(extension));
            _semaphoreClockSmart.setInterval(extension);
            previouslyExtended = true;
        }
        else {
            ui->semS_1_1->changeState();
            ui->semS_1_2->changeState();
            smartIt = 2;
            ui->semS_2_1->changeState();
            ui->semS_2_2->changeState();
            _semaphoreClockSmart.setInterval(SEMAPHORE2_XA);
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
            ui->semS_3_2->changeState();
            _semaphoreClockSmart.setInterval(SEMAPHORE3_XA);
            previouslyExtended = false;
        }
    }

    else if(smartIt == 3) {
        if(previouslyExtended == false) {
            float ext1 = fuzzyBrain(_s3_1->queueLength(), _s3_1->arrivalRate());
            float ext2 = fuzzyBrain(_s3_2->queueLength(), _s3_2->arrivalRate());
            int extension = qCeil(double(ext1 + ext2)/2);
            qDebug() << "Extension 3 : " << QString::number(double(extension));
            _semaphoreClockSmart.setInterval(extension);
            previouslyExtended = true;
        }
        else {
            ui->semS_3_1->changeState();
            ui->semS_3_2->changeState();
            smartIt = 4;
            ui->semS_4_1->changeState();
            ui->semS_4_1->changeState();
            _semaphoreClockSmart.setInterval(SEMAPHORE4_XA);
            previouslyExtended = false;
        }
    }

    else if (smartIt == 4 ) {
        if(previouslyExtended == false) {
            float ext1 = fuzzyBrain(_s4_1->queueLength(), _s4_1->arrivalRate());
            float ext2 = fuzzyBrain(_s4_2->queueLength(), _s4_2->arrivalRate());
            int extension = qCeil(double(ext1 + ext2)/2);
            _semaphoreClockSmart.setInterval(extension);
            qDebug() << "Extension 4 : " << QString::number(double(extension));
            previouslyExtended = true;
        }
        else {
            ui->semS_4_1->changeState();
            ui->semS_4_2->changeState();
            smartIt = 1;
            ui->semS_1_1->changeState();
            ui->semS_1_2->changeState();
            _semaphoreClockSmart.setInterval(SEMAPHORE1_XA);
            previouslyExtended = false;
        }
    }
    _semaphoreClockSmart.start();
}

void CrossroadXa::setupSemaphores()
{
    // Changing orientation, where neccessary
    ui->semC_2_1->setDirection(Orientation::LEFT1);
    ui->semC_2_2->setDirection(Orientation::LEFT1);
    ui->semC_4_1->setDirection(Orientation::LEFT1);
    ui->semC_4_2->setDirection(Orientation::LEFT1);

    ui->semS_2_1->setDirection(Orientation::LEFT1);
    ui->semS_2_2->setDirection(Orientation::LEFT1);
    ui->semS_4_1->setDirection(Orientation::LEFT1);
    ui->semS_4_2->setDirection(Orientation::LEFT1);

    // Setting green light to semaphores that start
    ui->semC_1_1->setState(State::GREEN);
    ui->semC_1_2->setState(State::GREEN);
    ui->semS_1_1->setState(State::GREEN);
    ui->semS_1_2->setState(State::GREEN);

    // Setting red light to rest of semaphores
    ui->semC_2_1->setState(State::RED);
    ui->semC_2_2->setState(State::RED);
    ui->semS_2_1->setState(State::RED);
    ui->semS_2_2->setState(State::RED);

    ui->semC_3_1->setState(State::RED);
    ui->semC_3_2->setState(State::RED);
    ui->semS_3_1->setState(State::RED);
    ui->semS_3_2->setState(State::RED);

    ui->semC_4_1->setState(State::RED);
    ui->semC_4_2->setState(State::RED);
    ui->semS_4_1->setState(State::RED);
    ui->semS_4_2->setState(State::RED);
}

void CrossroadXa::setupColumns()
{
    // Smart columns
    _s1_1 = new Column(this, 9, Direction::DOWN, 187, 15, 40, 15);
    _s1_1->attachSemaphore(ui->semS_1_1);
    _s1_1->setArrivalSensorPlace(3);
    connect(_s1_1, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _s3_1 = new Column(this, 9, Direction::DOWN, 242, 15, 40, 15);
    _s3_1->attachSemaphore(ui->semS_3_1);
    _s3_1->setArrivalSensorPlace(3);
    connect(_s3_1, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _s2_1 = new Column(this, 9, Direction::RIGHT, 526, 162, 15, 40);
    _s2_1->attachSemaphore(ui->semS_2_1);
    _s2_1->setArrivalSensorPlace(3);
    connect(_s2_1, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _s4_1 = new Column(this, 9, Direction::RIGHT, 526, 217, 15, 40);
    _s4_1->attachSemaphore(ui->semS_4_1);
    _s4_1->setArrivalSensorPlace(3);
    connect(_s4_1, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _s1_2 = new Column(this, 9, Direction::UP, 342, 490, 40, 15);
    _s1_2->attachSemaphore(ui->semS_1_2);
    _s1_2->setArrivalSensorPlace(3);
    connect(_s1_2, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _s3_2 = new Column(this, 9, Direction::UP, 287, 490, 40, 15);
    _s3_2->attachSemaphore(ui->semS_3_2);
    _s3_2->setArrivalSensorPlace(3);
    connect(_s3_2, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _s2_2 = new Column(this, 9, Direction::LEFT, 36, 317, 15, 40);
    _s2_2->attachSemaphore(ui->semS_2_2);
    _s2_2->setArrivalSensorPlace(3);
    connect(_s2_2, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _s4_2 = new Column(this, 9, Direction::LEFT, 36, 262, 15, 40);
    _s4_2->attachSemaphore(ui->semS_4_2);
    _s4_2->setArrivalSensorPlace(3);
    connect(_s4_2, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    // Conventional columns
    _c1_1 = new Column(this, 9, Direction::DOWN, 765, 15, 40, 15);
    _c1_1->attachSemaphore(ui->semC_1_1);
    _c1_1->setArrivalSensorPlace(0);
    connect(_c1_1, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _c3_1 = new Column(this, 9, Direction::DOWN, 820, 15, 40, 15);
    _c3_1->attachSemaphore(ui->semC_3_1);
    _c3_1->setArrivalSensorPlace(0);
    connect(_c3_1, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _c2_1 = new Column(this, 9, Direction::RIGHT, 1106, 165, 15, 40);
    _c2_1->attachSemaphore(ui->semC_2_1);
    _c2_1->setArrivalSensorPlace(0);
    connect(_c2_1, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _c4_1 = new Column(this, 9, Direction::RIGHT, 1106, 215, 15, 40);
    _c4_1->attachSemaphore(ui->semC_4_1);
    _c4_1->setArrivalSensorPlace(0);
    connect(_c4_1, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _c1_2 = new Column(this, 9, Direction::UP, 920, 490, 40, 15);
    _c1_2->attachSemaphore(ui->semC_1_2);
    _c1_2->setArrivalSensorPlace(0);
    connect(_c1_2, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _c3_2 = new Column(this, 9, Direction::UP, 865, 490, 40, 15);
    _c3_2->attachSemaphore(ui->semC_3_2);
    _c3_2->setArrivalSensorPlace(0);
    connect(_c3_2, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _c2_2 = new Column(this, 9, Direction::LEFT, 616, 319, 15, 40);
    _c2_2->attachSemaphore(ui->semC_2_2);
    _c2_2->setArrivalSensorPlace(0);
    connect(_c2_2, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);

    _c4_2 = new Column(this, 9, Direction::LEFT, 616, 265, 15, 40);
    _c4_2->attachSemaphore(ui->semC_4_2);
    _c4_2->setArrivalSensorPlace(0);
    connect(_c4_2, &Column::increaseTotalCars, this, &CrossroadXa::increaseSmart);
}

void CrossroadXa::setupTimeout()
{
    _timeoutClock.setParent(this);
    _timeoutClock.setInterval(TIMEOUT);

    connect(&_timeoutClock, &QTimer::timeout, _s1_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s1_2, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s2_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s2_2, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s3_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s3_2, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s4_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _s4_2, &Column::columnTimeout);

    connect(&_timeoutClock, &QTimer::timeout, _c1_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c1_2, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c2_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c2_2, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c3_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c3_2, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c4_1, &Column::columnTimeout);
    connect(&_timeoutClock, &QTimer::timeout, _c4_2, &Column::columnTimeout);

}

void CrossroadXa::setupSemaphoreTimer()
{
    _semaphoreClockConv.setInterval(SEMAPHORE1_XA);
    connect(&_semaphoreClockConv, &QTimer::timeout, this, &CrossroadXa::convTimeout);

    _semaphoreClockSmart.setInterval(SEMAPHORE1_XA);
    connect(&_semaphoreClockSmart, &QTimer::timeout, this, &CrossroadXa::smartTimeout);

    _semaphoreClockConv.start();
    _semaphoreClockSmart.start();
}

float CrossroadXa::fuzzyBrain(int queueLength, int arrivalRate)
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

    return result * MULTIPLIER_XA;

}

void CrossroadXa::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
        ui->buttonC1->click();
    if(event->key() == Qt::Key_S)
        ui->buttonC2->click();
    if(event->key() == Qt::Key_I)
        ui->buttonC3->click();
    if(event->key() == Qt::Key_K)
        ui->buttonC4->click();
    if(event->key() == Qt::Key_D)
        ui->buttonC6->click();
    if(event->key() == Qt::Key_F)
        ui->buttonC5->click();
    if(event->key() == Qt::Key_J)
        ui->buttonC7->click();
    if(event->key() == Qt::Key_U)
        ui->buttonC8->click();

}
