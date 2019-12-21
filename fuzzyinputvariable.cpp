#include "fuzzyinputvariable.hpp"

FuzzyInputVariable::FuzzyInputVariable(QString name, QVector<float> xcoords, QVector<float> ycoords, float x)
{
    m_name = name;
    m_x = x;
    if (xcoords.size() != ycoords.size())
        throw std::length_error("Function: FuzzyInputVariable, Error: Vectors X and Y are not same size.");
    for(int i = 0; i < xcoords.size(); ++i)
        m_points.append(QPair<float, float>(xcoords[i], ycoords[i]));
    m_mi = calculateMi();
}

float FuzzyInputVariable::mi()
{
    return m_mi;
}

QString FuzzyInputVariable::name()
{
    return m_name;
}

float FuzzyInputVariable::calculateMi()
{
    if (m_x < m_points[0].first)
        return  m_points[0].second;
    if (m_x > m_points.last().first)
        return m_points.last().second;
    for (int i = 0; i < m_points.size()-1; i++) {
        float x1 = m_points[i].first;
        float x2 = m_points[i+1].first;
        if ((x1 <= m_x) && (m_x < x2)) {
            float y1 = m_points[i].second;
            float y2 = m_points[i+1].second;
            return calculateYgivenX(x1, x2, y1, y2);
        }
    }
    return -1;
}

float FuzzyInputVariable::calculateYgivenX(float x1, float x2, float y1, float y2)
{
    if (std::abs(y1-y2) < float(EPS_CMP))
        return y1;
    if (y1 < y2)
        return (m_x-x1)/(x2-x1);
    return (x2-m_x)/(x2-x1);
}
