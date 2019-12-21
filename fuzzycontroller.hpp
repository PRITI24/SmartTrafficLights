#ifndef FUZZYCONTROLLER_HPP
#define FUZZYCONTROLLER_HPP

#include <fuzzyinput.hpp>
#include <fuzzyoutput.hpp>
#include <fuzzyrule.hpp>

#include <QDebug>

class FuzzyController
{
public:
    FuzzyController();
    void addInput(FuzzyInput *newInput);
    void addOutput(FuzzyOutput *newOutput);
    void addRule(FuzzyOutputVariable *output, FuzzyInputVariable *input1);
    void addRule(FuzzyOutputVariable *output, FuzzyInputVariable *input1, FuzzyInputVariable *input2, Logic l);
    FuzzyInput* is(QString name);
    FuzzyOutput* is(QString name, int);
    float solve();

private:
    QVector<FuzzyInput *> m_inputs;
    QVector<FuzzyOutput *> m_outputs;
    QVector<FuzzyRule *> m_rules;
};

#endif // FUZZYCONTROLLER_HPP
