#include "qlabelclickable.hpp"

QLabelClickable::QLabelClickable(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{

}

QLabelClickable::~QLabelClickable()
{

}

void QLabelClickable::mousePressEvent(QMouseEvent *)
{
   emit clicked();
}
