#ifndef FUZZYINPUTVARIABLE_HPP
#define FUZZYINPUTVARIABLE_HPP

#define EPS_CMP 0.0001

#include <QVector>
#include <QString>
#include <QPair>

class FuzzyInputVariable
{
public:
    FuzzyInputVariable(QString name, QVector<float> xcoords, QVector<float> ycoords, float x);
    float mi();
    QString name();

private:
    float calculateMi();
    float calculateYgivenX(float x1, float x2, float y1, float y2);

private:
    QString m_name;
    QVector<QPair<float, float>> m_points;
    float m_x;
    float m_mi;
};

#endif // FUZZYINPUTVARIABLE_HPP
