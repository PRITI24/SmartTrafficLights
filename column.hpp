#ifndef COLUMN_H
#define COLUMN_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <placeholder.hpp>
#include <semaphore.hpp>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Column : public QWidget
{
    Q_OBJECT
public:
    Column(QWidget *parent, int size, Direction d, int x, int y, int w, int h);
    void scheduleCar();
    void attachSemaphore(Semaphore *semaphore);
    void setArrivalSensorPlace(int place);
    bool columnFull();

public slots:
    void columnTimeout();
    int arrivalRate();
    int queueLength();

signals:
    void increaseTotalCars();

private:
    QVector<Placeholder*> m_column;
    int m_columnSize;
    Direction m_direction;
    int m_arrivalSensorPlace;
    int m_arrivalSensorAcc;
    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;
    bool m_scheduledCar = false;
    Semaphore *m_attachedSemaphore;

// Debugging functions
public:
    void changeType(int i, int type);

};

#endif // COLUMN_H
