#include "placeholder.h"

Placeholder::Placeholder()
{

}

void EmptySpace::draw()
{
    this->setStyleSheet("");
}

int EmptySpace::type() const
{
    return 0;
}

void Car::draw()
{
    this->setStyleSheet("");
}

int Car::type() const
{
    return 1;
}
