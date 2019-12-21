#include "fuzzyinput.hpp"

FuzzyInput::FuzzyInput(QString name)
{
    m_name = name;
    m_variables.resize(0);
}

void FuzzyInput::appendVariable(FuzzyInputVariable *newVariable)
{
    m_variables.append(newVariable);
}

FuzzyInputVariable *FuzzyInput::is(QString name)
{
    for(auto it = m_variables.begin(); it != m_variables.end(); it++)
        if ((*it)->name() == name)
            return (*it);
    return nullptr;
}

QString FuzzyInput::name()
{
    return m_name;
}
