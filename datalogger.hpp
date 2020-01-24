#ifndef DATALOGGER_HPP
#define DATALOGGER_HPP

#include <QWidget>
#include <QVector>
#include <QtMath>
#include <QDebug>
#include <algorithm>
#include "qcustomplot.hpp"

namespace Ui {
class DataLogger;
}

class DataLogger : public QWidget
{
    Q_OBJECT

public:
    DataLogger(QWidget *parent = nullptr, QVector<int> _smart = {}, QVector<int> _conv = {});
    ~DataLogger();
    void updateSmart(int value);
    void updateConvient(int value);
    void setTimeSpent(int smart, int conv);
    void prepareGraphs();
    void printVectors();

private:
    Ui::DataLogger *ui;
    QVector<double> _smartCars;
    QVector<double> _convientCars;
    QVector<double> _differences;
    double _diffMax = -99999;
    double _diffMin = +99999;
    int timeSmart = 0;
    int timeConv = 0;
};

#endif // DATALOGGER_HPP
