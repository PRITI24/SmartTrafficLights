#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include <QFrame>

class Placeholder : public QFrame
{
    Q_OBJECT
public:
    Placeholder(QWidget *parent);
    void draw();
    int type();
    void setType(int type);
    void setupSizePosition(int x, int y, int w, int h);
    void updatePosition(int x, int y);

private:
    int m_type = 0;
    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;
};

#endif // PLACEHOLDER_H
