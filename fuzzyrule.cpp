#include "fuzzyrule.hpp"

FuzzyRule::FuzzyRule(FuzzyInputVariable *i1, FuzzyInputVariable *i2, FuzzyOutputVariable *o1, Logic l)
{
    m_i1 = i1;
    m_i2 = i2;
    m_o1 = o1;

    if (l == Logic::AND)
        o1->setMi( std::max(o1->mi(), std::min(i1->mi(), i2->mi()) ));
    else
        o1->setMi( std::max(o1->mi(), std::max(i1->mi(), i2->mi()) ));
}
