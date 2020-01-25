#include "fuzzyoutputvariable.hpp"

FuzzyOutputVariable::FuzzyOutputVariable(QString name, QVector<float> xcoords, QVector<float> ycoords)
{
    m_name = name;
    if (xcoords.size() != ycoords.size())
        throw std::length_error("Function: FuzzyOutputVariable, Error: Vectors X and Y are not same size.");
    for(int i = 0; i < xcoords.size(); ++i)
        m_points.append(QPair<float, float>(xcoords[i], ycoords[i]));
    m_c = calculateC();
    m_mi = -1;
}

float FuzzyOutputVariable::c()
{
    return m_c;
}

void FuzzyOutputVariable::setMi(float mi)
{
    m_mi = mi;
}

float FuzzyOutputVariable::mi()
{
    return m_mi;
}

QString FuzzyOutputVariable::name()
{
    return m_name;
}

float FuzzyOutputVariable::calculateC()
{
    float sum = std::accumulate(m_points.begin(), m_points.end(), 0,
                                [] (float acc, QPair<float,float> x) { if (std::abs(1-x.second) < float(EPS_CMP))
                                                                            return acc + x.first;
                                                                        return acc; });
    float num = std::count_if(m_points.begin(), m_points.end(), [] (QPair<float,float> x) { return std::abs(1-x.second) < float(EPS_CMP); });

    return sum/num;
}
