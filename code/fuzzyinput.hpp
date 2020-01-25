#ifndef FUZZYINPUT_HPP
#define FUZZYINPUT_HPP

#include <fuzzyinputvariable.hpp>

class FuzzyInput
{
public:
    FuzzyInput(QString name);
    void appendVariable(FuzzyInputVariable *newVariable);
    FuzzyInputVariable* is(QString name);
    QString name();
private:
    QString m_name;
    QVector<FuzzyInputVariable*> m_variables;
};

#endif // FUZZYINPUT_HPP
