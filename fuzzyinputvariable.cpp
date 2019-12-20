#include "fuzzyinputvariable.hpp"

FuzzyInputVariable::FuzzyInputVariable(QString name, QVector<int> xcoords, QVector<int> ycoords)
{
    m_name = name;

    if (xcoords.size() != ycoords.size())
        throw std::length_error("FuzzyInputVariable : XCOORDS and YCOORDS not same size.");

    for(int i = 0; i < xcoords.size(); i++)
        m_points.append(QPair<int, int>(xcoords[i], ycoords[i]));
}

FuzzyInputVariable::FuzzyInputVariable(QString name, QVector<int> xcoords, QVector<int> ycoords, int x)
    : FuzzyInputVariable(name, xcoords, ycoords)
{
    m_x = x;
    m_mi = mi(x);
}

float FuzzyInputVariable::calculateYForGivenX(int x, int x1, int y1, int x2, int y2)
{
    if (y1 == y2)
        return y1;
    else if (y1 < y2)
        return (x - x1) / float(x2 -x1);
    else
        return (x2 - x) / float(x2 - x1);
}

float FuzzyInputVariable::mi(int x)
{

    if (x < m_points[0].first)
        return  m_points[0].second;
    if (x > m_points.last().first)
        return m_points.last().second;
    for (int i = 0; i < m_points.size()-1; i++) {
        int x1 = m_points[i].first;
        int x2 = m_points[i+1].first;
        if ((x >= x1) && (x < x2)) {
            int y1 = m_points[i].second;
            int y2 = m_points[i+1].second;
            return calculateYForGivenX(x, x1, y1, x2, y2);
        }
    }
    return -1;
}

float FuzzyInputVariable::mi()
{
    if(m_x != -1)
        return mi(m_x);
    return -1;
}

QString FuzzyInputVariable::name()
{
    return m_name;
}
