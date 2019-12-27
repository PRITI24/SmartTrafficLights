#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <tests.hpp>
#include <crossroadi.hpp>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void crossroadI();
    void crossroadTa();
    void crossroadTb();
    void crossroadTc();
    void crossroadXa();
    void crossroadXb();

private:
    Ui::MainWindow *ui;

    CrossroadI *m_i = nullptr;
};
#endif // MAINWINDOW_HPP
