#include "column.hpp"

Column::Column(QWidget *parent, int size, Direction d, int x, int y, int w, int h)
{
    this->setParent(parent);
    m_columnSize = size;
    m_direction = d;
    m_X = x;
    m_Y = y;
    m_Width = w;
    m_Height = h;
    m_scheduledCar = false;
    m_arrivalSensorAcc = 0;


    m_column.resize(0);
    for(int i = 0; i < m_columnSize; i++) {
        m_column.push_back(new Placeholder(this));
        switch (d) {
            case Direction::DOWN : m_column.last()->setupSizePosition(m_X, m_Y + i*m_Height, m_Width, m_Height); break;
            case Direction::UP :   m_column.last()->setupSizePosition(m_X, m_Y - i*m_Height, m_Width, m_Height); break;
            case Direction::LEFT:  m_column.last()->setupSizePosition(m_X + i*m_Width,  m_Y, m_Width, m_Height); break;
            case Direction::RIGHT: m_column.last()->setupSizePosition(m_X - i*m_Width,  m_Y, m_Width, m_Height); break;
        }

    }
}

void Column::changeType(int i, int type)
{
    m_column[i]->setType(type);
}

void Column::scheduleCar()
{
    m_scheduledCar = true;
}

void Column::columnTimeout()
{

    if(m_attachedSemaphore->state() == State::RED) {
        int n = m_columnSize-1;

        if(m_column[m_columnSize-1]->type() == 1) {
            n = m_columnSize-2;
        }

        for (int i = n; i > 0; i--)
            if ((m_column[i]->type() == 0) && (m_column[i-1]->type() == 1)) {
                m_column[i]->setType(1);
                m_column[i-1]->setType(0);
            }
    }
    else {  // If attached semaphore is green ...
        if(m_column[m_columnSize-1]->type())
            emit increaseTotalCars();

        for(int i = m_column.size()-2; i >= 0; i--) {
            m_column[i+1]->setType(m_column[i]->type());
        }
    }
    if(m_scheduledCar) {
        m_column[0]->setType(1);
        m_scheduledCar = false;
    }
    else {
        m_column[0]->setType(0);
    }

    // Arrival sensor
    if(m_column[m_arrivalSensorPlace]->type()) {
        m_arrivalSensorAcc++;
    }

}

int Column::arrivalRate()
{
    int tmp = m_arrivalSensorAcc;
    m_arrivalSensorAcc = 0;
    return tmp;
}

int Column::queueLength()
{
    int result = 0;
    for(int i = 0; i < m_columnSize; i++) {
        if(m_column[i]->type() == 1)
            result++;
    }
    return result;

}

int Column::totalCarsInColumn()
{
    return std::count_if(m_column.begin(), m_column.end(), [] (Placeholder *it) {if (it->type()) return true; return false ;});
}

void Column::attachSemaphore(Semaphore *semaphore)
{
    m_attachedSemaphore = semaphore;
}

void Column::setArrivalSensorPlace(int place)
{
    if(place < m_columnSize)
        m_arrivalSensorPlace = place;
}

bool Column::columnFull()
{
    for(int i = 0; i < m_columnSize; i++)
        if (!m_column[i]->type())
            return false;
    return true;
}
