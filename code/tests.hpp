#ifndef TESTS_HPP
#define TESTS_HPP

#include <QDebug>
#include <fuzzyinputvariable.hpp>
#include <fuzzyoutputvariable.hpp>
#include <fuzzycontroller.hpp>

class Test {
public:
        static void SmallFuelConsumption() {
            FuzzyInputVariable x("small", QVector<float>{3, 10}, QVector<float>{1,0}, 9);
            qDebug() << QString::number(double(x.mi()));
        }

        static void AverageFuelConsumption() {
            FuzzyInputVariable x("average", QVector<float>{7, 10, 12, 15}, QVector<float>{0,1,1,0}, 9);
            qDebug() << QString::number(double(x.mi()));
        }
        static void BigFuelConsumption() {
            FuzzyInputVariable x("big", QVector<float>{12, 15}, QVector<float>{0,1}, 9);
            qDebug() << QString::number(double(x.mi()));
        }
        static void BadReliability() {
            FuzzyInputVariable x("bad", QVector<float>{8,15}, QVector<float>{0,1}, 8);
            qDebug() << QString::number(double(x.mi()));
        }
        static void GoodReliability() {
            FuzzyInputVariable x("good", QVector<float>{5,10}, QVector<float>{1,0}, 8);
            qDebug() << QString::number(double(x.mi()));
        }
        static void SmallValueC() {
            FuzzyOutputVariable x("small", QVector<float>{7,15}, QVector<float>{1,0});
            qDebug() << QString::number(double(x.c()));
        }
        static void AverageValueC() {
            FuzzyOutputVariable x("average", QVector<float>{7,15,25,40}, QVector<float>{0,1,1,0});
            qDebug() << QString::number(double(x.c()));
        }
        static void BigValueC() {
            FuzzyOutputVariable x("big", QVector<float>{25,40}, QVector<float>{0,1});
            qDebug() << QString::number(double(x.c()));
        }

        static void runTests() {
            Test::SmallFuelConsumption();
            Test::AverageFuelConsumption();
            Test::BigFuelConsumption();

            Test::BadReliability();
            Test::GoodReliability();

            Test::SmallValueC();
            Test::AverageValueC();
            Test::BigValueC();
        }

        static void FuzzyControlerTDD() {
            FuzzyController x;

            x.addInput(new FuzzyInput("Hrana"));
            x.is("Hrana")->appendVariable(new FuzzyInputVariable("Los", QVector<float>{0,5}, QVector<float>{1,0}, 6.5));
            x.is("Hrana")->appendVariable(new FuzzyInputVariable("Prosek", QVector<float>{0,5,10}, QVector<float>{0,1,0}, 6.5));
            x.is("Hrana")->appendVariable(new FuzzyInputVariable("Dobar", QVector<float>{5,10}, QVector<float>{0,1}, 6.5));

            x.addInput(new FuzzyInput("Usluga"));
            x.is("Usluga")->appendVariable(new FuzzyInputVariable("Los", QVector<float>{0,5}, QVector<float>{1,0}, float(9.8)));
            x.is("Usluga")->appendVariable(new FuzzyInputVariable("Prosek", QVector<float>{0,5,10}, QVector<float>{0,1,0}, float(9.8)));
            x.is("Usluga")->appendVariable(new FuzzyInputVariable("Dobar", QVector<float>{5,10}, QVector<float>{0,1}, float(9.8)));

            x.addOutput(new FuzzyOutput("Baksis"));
            x.is("Baksis",0)->appendVariable(new FuzzyOutputVariable("Mala", QVector<float>{0,13}, QVector<float>{1,0}));
            x.is("Baksis",0)->appendVariable(new FuzzyOutputVariable("Srednja", QVector<float>{0,13,25}, QVector<float>{0,1,0}));
            x.is("Baksis",0)->appendVariable(new FuzzyOutputVariable("Velika", QVector<float>{13,25}, QVector<float>{0,1}));

            x.addRule(x.is("Baksis",0)->is("Mala"),    x.is("Hrana")->is("Los"),   x.is("Usluga")->is("Los"),  Logic::OR);
            x.addRule(x.is("Baksis",0)->is("Srednja"), x.is("Usluga")->is("Prosek"));
            x.addRule(x.is("Baksis",0)->is("Velika"),  x.is("Hrana")->is("Dobar"), x.is("Usluga")->is("Dobar"), Logic::OR);

            qDebug() << "SOLUTION : " << QString::number(double(x.solve()));
        }
};

#endif // TESTS_HPP
