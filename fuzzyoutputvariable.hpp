#ifndef FUZZYOUTPUTVARIABLE_HPP
#define FUZZYOUTPUTVARIABLE_HPP

#include <QObject>
#include <QString>
#include <QVector>
#include <QPair>

class FuzzyOutputVariable
{
public:
    FuzzyOutputVariable(QString name, QVector<int> xcoords, QVector<int> ycoords);
    void setMi(float miValueNew);
    float mi();
    float value();
private:
    QString m_name;
    QVector<QPair<int, int>> m_points;
    float m_mi;
    float m_value;
};

#endif // FUZZYOUTPUTVARIABLE_HPP
