#ifndef CROSSROADTA_HPP
#define CROSSROADTA_HPP

#define TIMEOUT 1150
#define SEMAPHORE1_TA 7000
#define SEMAPHORE2_TA 4000
#define SEMAPHORE3_TA 4000
#define MULTIPLIER_TA 200

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QtMath>
#include "column.hpp"
#include "fuzzycontroller.hpp"
#include "datalogger.hpp"

namespace Ui {
class CrossroadTa;
}

class CrossroadTa : public QWidget
{
    Q_OBJECT

public:
    explicit CrossroadTa(QWidget *parent = nullptr);
    ~CrossroadTa();

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
    void on_buttonC6_clicked();
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
    Ui::CrossroadTa *ui;

    // Columns
    Column *_s1_1;
    Column *_s1_2;
    Column *_s1_3;
    Column *_s2_1;
    Column *_s2_2;
    Column *_s3_1;

    Column *_c1_1;
    Column *_c1_2;
    Column *_c1_3;
    Column *_c2_1;
    Column *_c2_2;
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

};

#endif // CROSSROADTA_HPP
