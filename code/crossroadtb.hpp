#ifndef CROSSROADTB_HPP
#define CROSSROADTB_HPP

#define TIMEOUT 1150
#define SEMAPHORE1_TB 7000
#define SEMAPHORE2_TB 4000
#define SEMAPHORE3_TB 4000
#define MULTIPLIER_TB 200

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QtMath>
#include "column.hpp"
#include "fuzzycontroller.hpp"
#include "datalogger.hpp"

namespace Ui {
class CrossroadTb;
}

class CrossroadTb : public QWidget
{
    Q_OBJECT

public:
    explicit CrossroadTb(QWidget *parent = nullptr);
    ~CrossroadTb();

public slots:
    void increaseSmart();
    void increaseConv();

private slots:
    void on_startSimulation_clicked();
    void on_buttonC1_clicked();
    void on_buttonC3_clicked();
    void on_buttonC4_clicked();
    void on_buttonC2_clicked();
    void on_buttonC5_clicked();
    void convTimeout();
    void smartTimeout();

private:
    void setupSemaphores();
    void setupColumns();
    void setupTimeout();
    void setupSemaphoreTimer();
    void updateLogger();
    float fuzzyBrain(int queueLength, int arrivalRate);

protected:
    void keyPressEvent(QKeyEvent *event);


private:
    Ui::CrossroadTb *ui;

    // Columns
    Column *_s1_1;
    Column *_s1_2;
    Column *_s1_3;
    Column *_s2_1;
    Column *_s3_1;

    Column *_c1_1;
    Column *_c1_2;
    Column *_c1_3;
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

    // Data logger
    DataLogger *dataLogger;
    QVector<int> smartLogger;
    QVector<int> convientLogger;
    int spentTimeSmartLogger = 0;
    int spentTimeConvLogger = 0;

};

#endif // CROSSROADTB_HPP
