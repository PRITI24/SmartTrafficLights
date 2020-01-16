#ifndef CROSSROADXB_HPP
#define CROSSROADXB_HPP

#define TIMEOUT 1150
#define SEMAPHORE1_XA 7000
#define SEMAPHORE2_XA 7000
#define SEMAPHORE3_XA 4000
#define SEMAPHORE4_XA 4000
#define MULTIPLIER_XA 200

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QtMath>
#include <column.hpp>
#include <fuzzycontroller.hpp>

namespace Ui {
class CrossroadXb;
}

class CrossroadXb : public QWidget
{
    Q_OBJECT

public:
    explicit CrossroadXb(QWidget *parent = 0);
    ~CrossroadXb();
public slots:
    void increaseSmart();
    void increaseConv();

private slots:
    void on_startSimulation_clicked();
    void on_buttonC1_clicked();
    void on_buttonC2_clicked();
    void on_buttonC3_clicked();
    void on_buttonC4_clicked();
    void on_buttonC5_clicked();
    void on_buttonC6_clicked();
    void convTimeout();
    void smartTimeout();

private:
    void setupSemaphores();
    void setupColumns();
    void setupTimeout();
    void setupSemaphoreTimer();
    float fuzzyBrain(int queueLength, int arrivalRate);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::CrossroadXb *ui;

    // Columns
    Column* _s1_1;
    Column* _s1_2;
    Column* _s2_1;
    Column* _s2_2;
    Column* _s3_1;
    Column* _s4_1;

    Column* _c1_1;
    Column* _c1_2;
    Column* _c2_1;
    Column* _c2_2;
    Column* _c3_1;
    Column* _c4_1;

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

#endif // CROSSROADXB_HPP
