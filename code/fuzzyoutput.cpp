#include "fuzzyoutput.hpp"

FuzzyOutput::FuzzyOutput(QString name)
{
    m_name = name;
}

void FuzzyOutput::appendVariable(FuzzyOutputVariable *newVariable)
{
    m_variables.append(newVariable);
}

QString FuzzyOutput::name()
{
    return m_name;
}

QVector<FuzzyOutputVariable *>* FuzzyOutput::variables()
{
    return &m_variables;
}

FuzzyOutputVariable *FuzzyOutput::is(QString name)
{
    for(auto it = m_variables.begin(); it != m_variables.end(); it++)
        if ((*it)->name() == name)
            return (*it);
    return nullptr;
}
