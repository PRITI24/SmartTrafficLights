#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <tests.hpp>
#include <crossroadi.hpp>
#include <crossroadta.hpp>
#include <crossroadtb.hpp>
#include <crossroadtc.hpp>
#include <crossroadxa.hpp>
#include <crossroadxb.hpp>
#include <datalogger.hpp>

#include <QMainWindow>
#include <QVector>

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

    DataLogger *log = nullptr;

    CrossroadI *m_i = nullptr;
    CrossroadTa *m_ta = nullptr;
    CrossroadTb *m_tb = nullptr;
    CrossroadTc *m_tc = nullptr;
    CrossroadXa *m_xa = nullptr;
    CrossroadXb *m_xb = nullptr;
};
#endif // MAINWINDOW_HPP
