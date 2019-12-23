#include "semaphore.h"

Semaphore::Semaphore()
{

}

void Semaphore::changeState()
{
    if(m_state == State::GREEN) {
        m_state = State::RED;
    }
    else {
        m_state = State::GREEN;
        emit greenStart();
    }
}

State Semaphore::state()
{
    return m_state;
}
