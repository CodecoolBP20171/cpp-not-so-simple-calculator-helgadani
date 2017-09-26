//
// Created by eros on 25/09/17.
//

#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_CALCULATOR_H

#include <string>
#include <list>
#include "EquationElement.h"
using namespace std;


class Calculator {
public:
    double evaluate(string s);

    string removeSpaces(string s);

    int findOperatorMultiplyDivision(string s);

    int findOperatorAdditionSubtraction(string s);

    list<EquationElement> parseString(string s);
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_CALCULATOR_H
