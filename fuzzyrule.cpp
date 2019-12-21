#include "fuzzyrule.hpp"

FuzzyRule::FuzzyRule(FuzzyOutputVariable *output)
{
    m_output = output;
}

void FuzzyRule::addInput(FuzzyInputVariable *input1)
{
    m_input1 = input1;
    m_input2 = nullptr;
    m_output->setMi(std::max(m_output->mi(), m_input1->mi()));
}

void FuzzyRule::addInput(FuzzyInputVariable *input1, FuzzyInputVariable *input2, Logic l)
{
    m_input1 = input1;
    m_input2 = input2;

    if (l == Logic::AND)
        m_output->setMi(std::max(m_output->mi(), std::min(m_input1->mi(), m_input2->mi())));
    else
        m_output->setMi(std::max(m_output->mi(), std::max(m_input1->mi(), m_input2->mi())));
}
