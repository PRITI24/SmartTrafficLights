#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <QFrame>
#include <QDebug>
#include <QTimer>

enum State {
    GREEN,
    RED
};

class Semaphore : public QFrame
{
    Q_OBJECT
public:
    Semaphore(QWidget *parent);
    void setState(State newState);

public slots:
    void changeState();
    State state();

signals:
    void changedState(State s);

private:
    State m_state;
};

#endif // SEMAPHORE_H
