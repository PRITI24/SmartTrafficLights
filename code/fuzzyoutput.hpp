#ifndef FUZZYOUTPUT_HPP
#define FUZZYOUTPUT_HPP

#include <fuzzyoutputvariable.hpp>

class FuzzyOutput
{
public:
    FuzzyOutput(QString name);
    void appendVariable(FuzzyOutputVariable *newVariable);
    FuzzyOutputVariable* is(QString name);
    QString name();
    QVector<FuzzyOutputVariable *> *variables();

private:
    QString m_name;
    QVector<FuzzyOutputVariable *> m_variables;
};

#endif // FUZZYOUTPUT_HPP
