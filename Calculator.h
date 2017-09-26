#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_CALCULATOR_H

#include <string>
#include <list>
#include <vector>
#include "EquationElement.h"

using namespace std;


class Calculator {
public:

    string correctedEquationString;
    vector<EquationElement> equationVector;
    vector<string> digits {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."};
    vector<string> operators {"+", "-", "*", "/", "^", "root"};
    bool operatorPrecedence1 = true;
    bool operatorPrecedence2 = true;
    bool operatorPrecedence3 = true;

    vector<EquationElement> parseEquationString(string equationString);
    double evaluate(string equationString);
    void correctInputString(string equationString);
    void doMath();
    void doOperation(int index);
    bool isValidExpression();
    int findOperatorRootPow();
    int findOperatorMultiplicationDivision();
    int findOperatorAdditionSubtraction();
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_CALCULATOR_H
