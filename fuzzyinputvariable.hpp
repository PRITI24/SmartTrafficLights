#ifndef FUZZYINPUTVARIABLE_HPP
#define FUZZYINPUTVARIABLE_HPP

#include <QObject>
#include <QVector>
#include <QPair>
#include <QErrorMessage>

class FuzzyInputVariable
{
public:
    FuzzyInputVariable(QString name, QVector<int> xcoords, QVector<int> ycoords);
    FuzzyInputVariable(QString name, QVector<int> xcoords, QVector<int> ycoords, int x);
    float mi(int x);
    float mi();
    QString name();
    float calculateYForGivenX(int x, int x1, int y1, int x2, int y2);

private:
    QString m_name;
    QVector<QPair<int, int>> m_points;
    int m_x = -1;
    float m_mi;
};

#endif // FUZZYINPUTVARIABLE_HPP
