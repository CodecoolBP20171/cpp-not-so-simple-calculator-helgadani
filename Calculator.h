//
// Created by eros on 25/09/17.
//

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

    double evaluate(string s);

    string removeSpaces(string s);

    int findOperatorMultiplyDivision();

    int findOperatorAdditionSubtraction();

    vector<EquationElement> parseString(string s);

    void doMath(int i);
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_CALCULATOR_H
