#include "fuzzyoutputvariable.hpp"

FuzzyOutputVariable::FuzzyOutputVariable(QString name, QVector<int> xcoords, QVector<int> ycoords)
{
    m_name = name;
    float sumX = 0;
    int numberOnes = 0;

    if(xcoords.size() != ycoords.size())
       throw std::length_error("FuzzyInputVariable : XCOORDS and YCOORDS not same size.");

    for(int i = 0; i < xcoords.size(); i++) {
        m_points.append(QPair<int, int>(xcoords[i], ycoords[i]));
        if (ycoords[i] == 1) {
            sumX += xcoords[i];
            ++numberOnes;
        }
    }

    m_mi = 0;
    m_value = sumX / float(numberOnes);
}

void FuzzyOutputVariable::setMi(float miValueNew)
{
    m_mi = miValueNew;
}

float FuzzyOutputVariable::mi()
{
    return m_mi;
}

float FuzzyOutputVariable::value()
{
    return m_value;
}
