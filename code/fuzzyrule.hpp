#ifndef FUZZYRULE_HPP
#define FUZZYRULE_HPP

#include <fuzzyinputvariable.hpp>
#include <fuzzyoutputvariable.hpp>

enum Logic {
    AND,
    OR
};

class FuzzyRule
{
public:
    FuzzyRule(FuzzyOutputVariable *output);
    void addInput(FuzzyInputVariable *input1);
    void addInput(FuzzyInputVariable *input1, FuzzyInputVariable *input2, Logic l);

private:
    FuzzyOutputVariable *m_output;
    FuzzyInputVariable *m_input1;
    FuzzyInputVariable *m_input2;
};

#endif // FUZZYRULE_HPP
