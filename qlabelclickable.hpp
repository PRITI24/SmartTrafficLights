#ifndef QLABELCLICKABLE_HPP
#define QLABELCLICKABLE_HPP

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <Qt>

class QLabelClickable : public QLabel
{
    Q_OBJECT
public:
    explicit QLabelClickable(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~QLabelClickable();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // QLABELCLICKABLE_HPP
