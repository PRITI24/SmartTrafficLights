#include "semaphore.hpp"

Semaphore::Semaphore(QWidget *parent)
{
    this->setParent(parent);

}

void Semaphore::setState(State newState)
{
    m_state = newState;
    if(m_state == State::GREEN)
        this->setStyleSheet("image: url(:/images/images/mainwindow/greenSemaphore.png);");
    else
        this->setStyleSheet("image: url(:/images/images/mainwindow/redSemaphore.png);");
}

void Semaphore::changeState()
{
    if(m_state == State::GREEN) {
        m_state = State::RED;
        this->setStyleSheet("image: url(:/images/images/mainwindow/redSemaphore.png);");
        emit changedState(State::RED);
    }
    else {
        m_state = State::GREEN;
        this->setStyleSheet("image: url(:/images/images/mainwindow/greenSemaphore.png);");
        emit changedState(State::GREEN);
    }
}

State Semaphore::state()
{
    return m_state;
}
