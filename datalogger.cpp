#include "datalogger.hpp"
#include "ui_datalogger.h"

DataLogger::DataLogger(QWidget *parent, QVector<int> _smart, QVector<int> _conv) :
    QWidget(parent),
    ui(new Ui::DataLogger)
{

    ui->setupUi(this);

    std::for_each(_smart.begin(), _smart.end(), [this] (const int &i) {_smartCars.push_back(double(i));});
    std::for_each(_conv.begin(), _conv.end(), [this] (const int &i) {_convientCars.push_back(double(i));});

    while( (_smartCars.first() == 0) && (_convientCars.first() == 0) ) {
        _smartCars.remove(0);
        _convientCars.remove(0);
    }
    _smartCars.push_front(0);
    _convientCars.push_front(0);

    if(_smartCars.size() != _convientCars.size()) {
        int difference =  _convientCars.size() - _smartCars.size();
        if(difference > 0) {
            while(difference != 0) {
                _smartCars.push_back(_convientCars.last());
                --difference;
            }
        }
        if(difference < 0) {
            while(difference != 0) {
                _smartCars.push_back(_convientCars.last());
                ++difference;
            }
        }
    }

    for(int i = 0; i < _smartCars.size(); ++i)
        _differences.push_back(_smartCars[i] - _convientCars[i]);

    for(int i = 0; i < _differences.size(); ++i) {
        if(_differences[i] > _diffMax)
            _diffMax = _differences[i];
        if(_differences[i] < _diffMin)
            _diffMin = _differences[i];
    }

    prepareGraphs();
    printVectors();
}

DataLogger::~DataLogger()
{
    delete ui;
}

void DataLogger::updateSmart(int value)
{
    _smartCars.push_back(double(value));
}

void DataLogger::updateConvient(int value)
{
    _smartCars.push_back(double(value));
}

void DataLogger::prepareGraphs()
{
    int n = _convientCars.size();

    QVector<double> timeline;
    for(int i = 0; i < n; i++)
        timeline.push_back(i);

    // Creating smartGraph
    ui->smartGraph->addGraph();
    ui->smartGraph->graph(0)->setData(timeline, _smartCars);
    ui->smartGraph->xAxis->setLabel("Time");
    ui->smartGraph->yAxis->setLabel("Total cars passed : Smart system");
    ui->smartGraph->xAxis->setRange(0, n+1);
    ui->smartGraph->yAxis->setRange(0, _smartCars.last()+1);

    // Creating convientGraph
    ui->convientGraph->addGraph();
    ui->convientGraph->graph(0)->setData(timeline, _convientCars);
    ui->convientGraph->xAxis->setLabel("Time");
    ui->convientGraph->yAxis->setLabel("Total cars passed : Convient system");
    ui->convientGraph->xAxis->setRange(0, n+1);
    ui->convientGraph->yAxis->setRange(0, _convientCars.last()+1);

    // Creating differenceGraph
    ui->differenceGraph->addGraph();
    ui->differenceGraph->graph(0)->setData(timeline, _differences);
    ui->differenceGraph->xAxis->setLabel("Time");
    ui->differenceGraph->yAxis->setLabel("Differences between two systems");
    ui->differenceGraph->xAxis->setRange(0, n+1);
    ui->differenceGraph->yAxis->setRange(_diffMin, _diffMax);

    ui->lTotalCarsInSmart->setText( QString::number(_smartCars.size()) );
    ui->lTotalCarsInConvient->setText( QString::number(_convientCars.size()));
    ui->lMaxDifferenceSmart->setText( QString::number(_diffMax) );
    ui->lMaxDifferenceConv->setText( QString::number(std::fabs(_diffMin)));
}

void DataLogger::printVectors()
{
    QString s = "S: ";
    for(auto it = _smartCars.begin(); it != _smartCars.end(); it++) {
        s = s + QString::number(*it) + " ";
    }
    qDebug() << s;

    QString c = "C: ";
    for(auto it = _convientCars.begin(); it != _convientCars.end(); it++) {
        c = c + QString::number(*it) + " ";
    }
    qDebug() << c;

}
