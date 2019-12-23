#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include <QFrame>

class Placeholder : public QFrame
{
    Q_OBJECT
public:
    Placeholder();
    void drow();
    int type() const;
};

class EmptySpace : public Placeholder
{
public:
    void draw();
    int type();
};

class Car : public Placeholder
{
public:
    void draw();
    int type();
};

#endif // PLACEHOLDER_H
