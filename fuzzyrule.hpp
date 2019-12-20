#ifndef FUZZYRULE_HPP
#define FUZZYRULE_HPP

#include <fuzzyinputvariable.hpp>
#include <fuzzyoutputvariable.hpp>

enum class Logic
{
    AND,
    OR
};

class FuzzyRule
{
public:
    FuzzyRule(FuzzyInputVariable *i1, FuzzyInputVariable *i2, FuzzyOutputVariable *o1, Logic l);
private:
    FuzzyInputVariable *m_i1;
    FuzzyInputVariable *m_i2;
    FuzzyOutputVariable *m_o1;
    Logic m_logic;
};

#endif // FUZZYRULE_HPP

