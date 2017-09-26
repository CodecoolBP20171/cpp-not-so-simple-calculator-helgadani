#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_CALCULATOR_H

#include <string>
#include <list>
#include <vector>
#include "EquationElement.h"

using namespace std;


class Calculator {
public:

    vector<EquationElement> equationVector;

    string removeSpaces(string equationString);

    double evaluate(string equationString);

    int findOperatorMultiplyDivision();

    int findOperatorAdditionSubtraction();

    vector<EquationElement> parseEquationString(string equationString);

    void doMath(int index);
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_CALCULATOR_H
