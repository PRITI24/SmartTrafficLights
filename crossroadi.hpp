#ifndef CROSSROADI_HPP
#define CROSSROADI_HPP

#define TIMEOUT 1330
#define GREENLIGHT 8000
#define REDLIGHT 4000

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QtMath>
#include "column.hpp"
#include "fuzzycontroller.hpp"

namespace Ui {
class CrossroadI;
}

class CrossroadI : public QWidget
{
    Q_OBJECT

public:
    explicit CrossroadI(QWidget *parent = nullptr);
    ~CrossroadI();

private slots:
    void onstartSimButtonClicked();

    void scheduledCarForSColumn1();
    void scheduledCarForSColumn2();
    void scheduledCarForCColumn1();
    void scheduledCarForCColumn2();

    void s1Timeout();
    void c1Timeout();

private:
    void setupSemaphores();
    void setupColumns();
    void setupTimeout();
    void setupSemaphoreTimers();
    float fuzzyBrain(int queueLength, int arrivalRate);

private:
    Ui::CrossroadI *ui;

    QPushButton *startSimButton;
    QPushButton *addSColumn1Button;
    QPushButton *addSColumn2Button;

    QTimer timeoutClock;

    QTimer _sem1Green;
    QTimer _sem1Red;


    QTimer _s1Timer;
    QTimer _c1Timer;

    Column *_Scolumn1;
    Column *_Scolumn2;
    Column *_Ccolumn1;
    Column *_Ccolumn2;

    FuzzyController *_controller1;

    bool previouslyExtended = false;

};

#endif // CROSSROADI_HPP
