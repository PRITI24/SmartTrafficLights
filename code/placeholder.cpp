#include "placeholder.hpp"

Placeholder::Placeholder(QWidget *parent)
{
    this->setParent(parent);
    this->draw();
}

void Placeholder::draw()
{
    if(m_type) {
        this->setStyleSheet("image: url(:/images/images/mainwindow/car.png);");
    }
    else {
        this->setStyleSheet("");
    }
}

int Placeholder::type()
{
    return m_type;
}

void Placeholder::setType(int type)
{
    m_type = type;
    draw();
}


void Placeholder::setupSizePosition(int x, int y, int w, int h)
{
    m_X = x;
    m_Y = y;
    m_Width = w;
    m_Height = h;
    this->setGeometry(m_X, m_Y, m_Width, m_Height);

}

void Placeholder::updatePosition(int x, int y)
{
    // DOWN, UP
    if(y)
        m_Y = m_Y + x*m_Height;
    // LEFT, RIGHT
    else
        m_X = m_X + y*m_Width;
    this->setGeometry(m_X, m_Y, m_Width, m_Height);
}
