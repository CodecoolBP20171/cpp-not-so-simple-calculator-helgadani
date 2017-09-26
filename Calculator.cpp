//
// Created by eros on 25/09/17.
//
#include <iostream>
#include <vector>
#include "Calculator.h"
#include <algorithm>
#include <stdlib.h>
#include "EquationElement.h"

using namespace std;

double Calculator::evaluate(string s) {
    string sd = removeSpaces(s);
    equationVector = parseString(sd);
    //for(EquationElement element: equationList){
    //    element.print();
    //}
    int operatorIndex = findOperatorAdditionSubtraction();
    doMath(operatorIndex);



    //cout << sd << endl;
    //cout << findOperatorMultiplyDivision(sd) << endl;
    //cout << findOperatorAdditionSubtraction(sd) << endl;
    //int operatorIndex = findOperatorAdditionSubtraction(equationList);
    //cout << operatorIndex << endl;
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

int Calculator::findOperatorMultiplyDivision() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].value == "/" || equationVector[i].value == "*") {
            return i;
        }
    }
    return -1;
}

int Calculator::findOperatorAdditionSubtraction() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].value == "+" || equationVector[i].value == "-") {
            return i;
        }
    }
    return -1;
}

vector<EquationElement> Calculator::parseString(string s){
    vector<EquationElement> result;
    vector<string> digits {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."};
    vector<string> operators {"+", "-", "*", "/", "^"};
    string numbers;
    string op;
    for (int i = 0; i < s.size(); ++i) {
        char charFromString = s[i];
        bool isNumber = find(digits.begin(), digits.end(), string(1, charFromString)) != digits.end();
        if (isNumber) {
            if (op != "") {
                EquationElement character(op, false);
                result.push_back(character);
                op = "";
            }
            numbers += charFromString;
        } else {
            if (numbers != "") {
                EquationElement character(numbers, true);
                result.push_back(character);
                numbers = "";
            }
            op += charFromString;
        }
        if (i == s.size() - 1) {
            if (numbers == "") {
                EquationElement character(op, false);
                result.push_back(character);
            } else {
                EquationElement character(numbers, true);
                result.push_back(character);
            }
        }
    }
    return result;
}

void Calculator::doMath(int i) {
    for(EquationElement element: equationVector){
        element.print();
    }

    string stringBefore = equationVector[i-1].value;
    string stringAfter = equationVector[i+1].value;
    double numberBefore = strtod(stringBefore.c_str(), NULL);
    double numberAfter = strtod(stringAfter.c_str(), NULL);
    double result;

    cout << stringBefore << " " << stringAfter << endl;
    string op = equationVector[i].value;
    if(op == "*") {
        result = numberBefore * numberAfter;
    } else if(op == "+"){
        result = numberBefore + numberAfter;
    }  else if(op == "-"){
        result = numberBefore - numberAfter;
    }  else if(op == "/"){
        result = numberBefore / numberAfter;
    }
    equationVector[i-1].value = to_string(result);
    equationVector.erase(equationVector.begin() + i, equationVector.begin() + i + 1);

    //cout << result;
    //for(EquationElement element1: equationVector){
    //    element1.print();
    //}



}



