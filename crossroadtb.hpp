#ifndef CROSSROADTB_HPP
#define CROSSROADTB_HPP

#include <QWidget>

namespace Ui {
class CrossroadTb;
}

class CrossroadTb : public QWidget
{
    Q_OBJECT

public:
    explicit CrossroadTb(QWidget *parent = nullptr);
    ~CrossroadTb();

private:
    Ui::CrossroadTb *ui;
};

#endif // CROSSROADTB_HPP
