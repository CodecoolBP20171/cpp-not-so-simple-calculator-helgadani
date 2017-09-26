//
// Created by eros on 25/09/17.
//
#include <iostream>
#include "Calculator.h"
#include "EquationElement.h"

using namespace std;

double Calculator::evaluate(string s) {
    string sd = removeSpaces(s);
    list<EquationElement> equationList = parseString(sd);
    cout << sd << endl;
    //cout << findOperatorMultiplyDivision(sd) << endl;
    //cout << findOperatorAdditionSubtraction(sd) << endl;
    int operatorIndex = findOperatorAdditionSubtraction(sd);
    return 1.0;
}

string Calculator::removeSpaces(string s) {
    string newOperation = "";
    for (unsigned int i = 0; i < s.size(); ++i) {
        if (s[i] != ' ') {
            newOperation += s[i];
        }
    }
    return newOperation;
}

int Calculator::findOperatorMultiplyDivision(string s) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '/' || s[i] == '*') {
            return i;
        }
    }
    return -1;
}

int Calculator::findOperatorAdditionSubtraction(string s) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '-' || s[i] == '+') {
            return i;
        }
    }
    return -1;
}

list<EquationElement> Calculator::parseString(string s){
    list<EquationElement> result;
    EquationElement element("1");

    //result.insert("1");
    return result;
}

