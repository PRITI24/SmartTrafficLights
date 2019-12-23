#ifndef COLUMN_H
#define COLUMN_H

#include <QObject>
#include <QVector>
#include <placeholder.h>
#include <semaphore.h>

class Column
{
    Q_OBJECT
public:
    Column();
    int lengthSensor();
    int arrivalSensor();

public slots:
    void resetArrivalSensorAcc();

private:
    QVector<Placeholder*> m_column;
    int m_columnSize;
    int m_arrivalSensorPlace;
    int m_arrivalSensorAcc;
    Semaphore *attachedSemaphore;

};

#endif // COLUMN_H
