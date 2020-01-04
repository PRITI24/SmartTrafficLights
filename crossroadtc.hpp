#ifndef CROSSROADTC_HPP
#define CROSSROADTC_HPP

#define TIMEOUT 1150
#define SEMAPHORE1 7000
#define SEMAPHORE2 4000
#define SEMAPHORE3 3000
#define MULTIPLIER 180

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QtMath>
#include "column.hpp"
#include "fuzzycontroller.hpp"

namespace Ui {
class CrossroadTc;
}

class CrossroadTc : public QWidget
{
    Q_OBJECT

public:
    explicit CrossroadTc(QWidget *parent = 0);
    ~CrossroadTc();
public slots:
    void increaseSmart();
    void increaseConv();

private slots:
    void on_startSimulation_clicked();
    void on_buttonC1_clicked();
    void on_buttonC2_clicked();
    void on_buttonC3_clicked();
    void convTimeout();
    void smartTimeout();

private:
    void setupSemaphores();
    void setupColumns();
    void setupTimeout();
    void setupSemaphoreTimer();
    float fuzzyBrain(int queueLength, int arrivalRate);


private:
    Ui::CrossroadTc *ui;

    // Columns
    Column *_s1_1;
    Column *_s2_1;
    Column *_s3_1;

    Column *_c1_1;
    Column *_c2_1;
    Column *_c3_1;

    // Car counter
    int _smartTotal = 0;
    int _convTotal = 0;

    // Timers
    QTimer _timeoutClock;
    QTimer _semaphoreClockConv;
    QTimer _semaphoreClockSmart;

    // Additional fields
    int convIt = 1;
    int smartIt = 1;
    bool previouslyExtended = false;
    FuzzyController *_controller1;

};

#endif // CROSSROADTC_HPP
