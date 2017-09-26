//
// Created by eros on 25/09/17.
//
#include <iostream>
#include <vector>
#include "Calculator.h"
#include <algorithm>
#include "EquationElement.h"

using namespace std;

double Calculator::evaluate(string s) {
    string sd = removeSpaces(s);
    vector<EquationElement> equationList = parseString(sd);
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
    for (EquationElement element : result) {
        cout << element.value << endl;
        cout << element.isNumber << endl;
    }

    //result.insert("1");
    return result;
}

