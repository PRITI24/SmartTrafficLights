#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <QFrame>
#include <QDebug>
#include <QTimer>

enum State {
    GREEN,
    RED
};

enum Orientation {
    UP1,
    LEFT1
};

class Semaphore : public QFrame
{
    Q_OBJECT
public:
    Semaphore(QWidget *parent);
    void setState(State newState);
    void setDirection(Orientation newDirection);

public slots:
    void changeState();
    State state();

signals:
    void changedState(State s);

private:
    State m_state;
    Orientation m_direction = Orientation::UP1;
};

#endif // SEMAPHORE_H
