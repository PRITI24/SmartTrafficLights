#ifndef FUZZYOUTPUTVARIABLE_HPP
#define FUZZYOUTPUTVARIABLE_HPP

#define EPS_CMP 0.0001

#include <QString>
#include <QVector>
#include <QPair>

class FuzzyOutputVariable
{
public:
    FuzzyOutputVariable(QString name, QVector<float> xcoords, QVector<float> ycoords);
    float c();
    void setMi(float mi);
    float mi();
    QString name();
private:
    float calculateC();

private:
    QString m_name;
    QVector<QPair<float, float>> m_points;
    float m_c;
    float m_mi;
};

#endif // FUZZYOUTPUTVARIABLE_HPP
