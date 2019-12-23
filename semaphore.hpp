#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <QObject>

enum State {
    GREEN,
    RED
};

class Semaphore : public QObject
{
    Q_OBJECT
public:
    Semaphore();

public slots:
    void changeState();
    State state();

signals:
    void greenStart();

private:
    State m_state;

};

#endif // SEMAPHORE_H
