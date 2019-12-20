#include "tests.hpp"

void Tests::Test1()
{
    // EXAMPLE 1 : FuelConsumption and Reliability => Value

    QVector<FuzzyInputVariable *> fuelConsumption;
    fuelConsumption.append(new FuzzyInputVariable("small", QVector<int>{3,10}, QVector<int>{1,0}, 9));
    fuelConsumption.append(new FuzzyInputVariable("average", QVector<int>{7,10,12,15}, QVector<int>{0,1,1,0}, 9));
    fuelConsumption.append(new FuzzyInputVariable("big", QVector<int>{12,15}, QVector<int>{0,1}, 9));

    QVector<FuzzyInputVariable *> reliability;
    reliability.append(new FuzzyInputVariable("high", QVector<int>{5,10}, QVector<int>{1,0}, 8));
    reliability.append(new FuzzyInputVariable("low", QVector<int>{8,15}, QVector<int>{0,1}, 8));

    QVector<FuzzyOutputVariable *> value;
    value.append(new FuzzyOutputVariable("small", QVector<int>{7,15}, QVector<int>{1,0}));
    value.append(new FuzzyOutputVariable("average", QVector<int>{7,15,25,40}, QVector<int>{0,1,1,0}));
    value.append(new FuzzyOutputVariable("big", QVector<int>{25,40}, QVector<int>{0,1}));

    QVector<FuzzyRule *> rules;
    rules.append(new FuzzyRule(fuelConsumption[0], reliability[0], value[2], Logic::AND));
    rules.append(new FuzzyRule(fuelConsumption[0], reliability[1], value[1], Logic::AND));
    rules.append(new FuzzyRule(fuelConsumption[1], reliability[0], value[1], Logic::AND));
    rules.append(new FuzzyRule(fuelConsumption[1], reliability[1], value[1], Logic::AND));
    rules.append(new FuzzyRule(fuelConsumption[2], reliability[0], value[1], Logic::AND));
    rules.append(new FuzzyRule(fuelConsumption[2], reliability[1], value[0], Logic::AND));

    float numerator = 0;
    float denominator = 0;
    for(auto outputV : value) {
        numerator += outputV->mi() * outputV->value();
        denominator += outputV->mi();
    }
    float solution = numerator / denominator;

    qDebug() << "Value: " << QString::number(double(solution));
}
