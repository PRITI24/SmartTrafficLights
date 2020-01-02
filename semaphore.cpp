#include "semaphore.hpp"

Semaphore::Semaphore(QWidget *parent)
{
    this->setParent(parent);
}


void Semaphore::setState(State newState)
{
    m_state = newState;

    if(m_state == State::GREEN) {
        switch (m_direction) {
        case Orientation::UP1 :
            this->setStyleSheet("image: url(:/images/images/mainwindow/greenSemaphoreUP.png);"); break;
        case Orientation::LEFT1 :
            this->setStyleSheet("image: url(:/images/images/mainwindow/greenSemaphoreLEFT.png);"); break;
        }
    }
    else {
        switch (m_direction) {
        case Orientation::UP1 :
            this->setStyleSheet("image: url(:/images/images/mainwindow/redSemaphoreUP.png);"); break;
        case Orientation::LEFT1 :
            this->setStyleSheet("image: url(:/images/images/mainwindow/redSemaphoreLEFT.png);"); break;
        }
    }

}

void Semaphore::setDirection(Orientation newDirection)
{
    m_direction = newDirection;
}

void Semaphore::changeState()
{
    if(m_state == State::GREEN) {
        m_state = State::RED;
        switch (m_direction) {
        case Orientation::UP1 :
            this->setStyleSheet("image: url(:/images/images/mainwindow/redSemaphoreUP.png);"); break;
        case Orientation::LEFT1 :
            this->setStyleSheet("image: url(:/images/images/mainwindow/redSemaphoreLEFT.png);"); break;
        }
    }
    else {
        m_state = State::GREEN;
        switch (m_direction) {
        case Orientation::UP1 :
            this->setStyleSheet("image: url(:/images/images/mainwindow/greenSemaphoreUP.png);"); break;
        case Orientation::LEFT1 :
            this->setStyleSheet("image: url(:/images/images/mainwindow/greenSemaphoreLEFT.png);"); break;
        }
    }
}

State Semaphore::state()
{
    return m_state;
}
