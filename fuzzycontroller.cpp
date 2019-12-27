#include "fuzzycontroller.hpp"

FuzzyController::FuzzyController()
{
    m_inputs.resize(0);
    m_outputs.resize(0);
    m_rules.resize(0);
}

void FuzzyController::addInput(FuzzyInput *newInput)
{
    m_inputs.append(newInput);
}

void FuzzyController::addOutput(FuzzyOutput *newOutput)
{
    m_outputs.append(newOutput);
}

void FuzzyController::addRule(FuzzyOutputVariable *output, FuzzyInputVariable *input1)
{
    FuzzyRule *newRule = new FuzzyRule(output);
    newRule->addInput(input1);
    m_rules.append(newRule);
}

void FuzzyController::addRule(FuzzyOutputVariable *output, FuzzyInputVariable *input1, FuzzyInputVariable *input2, Logic l)
{
    FuzzyRule *newRule = new FuzzyRule(output);
    newRule->addInput(input1,input2, l);
    m_rules.append(newRule);
}


FuzzyInput *FuzzyController::is(QString name)
{
    for(auto it = m_inputs.begin(); it != m_inputs.end(); it++)
        if ((*it)->name() == name)
            return (*it);
    return nullptr;
}

FuzzyOutput *FuzzyController::is(QString name, int)
{
    for(auto it = m_outputs.begin(); it != m_outputs.end(); it++)
        if ((*it)->name() == name)
            return (*it);
    return nullptr;
}

float FuzzyController::solve()
{
   auto output = m_outputs.last()->variables();
   float up = 0, down = 0;

   for(auto it = output->begin(); it != output->end(); it++) {
        //qDebug() << (*it)->name() << " c: " << (*it)->c() << " mi :" << (*it)->mi();
        up += (*it)->mi() * (*it)->c();
        down += (*it)->mi();
   }
   return up / down;
}
