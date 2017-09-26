#include <iostream>
#include <vector>
#include "Calculator.h"
#include <algorithm>
#include "EquationElement.h"

using namespace std;

double Calculator::evaluate(string equationString) {
    string correctedEquationString = correctInputString(equationString);
    if (correctedEquationString == "") return 0;

    equationVector = parseEquationString(correctedEquationString);
    //for(EquationElement element: equationList){
    //    element.print();
    //}
    bool power = true;
    bool multiply = true;
    bool addition = true;
    while (power) {
        int operatorIndex = findOperatorRootPow();
        if (operatorIndex > -1) {
            doMath(operatorIndex);
        } else {
            power = false;
        }
    }
    while (multiply) {
        int operatorIndex = findOperatorMultiplicationDivision();
        if (operatorIndex > -1) {
            doMath(operatorIndex);
        } else {
            multiply = false;
        }
    }
    while (addition) {
        int operatorIndex = findOperatorAdditionSubtraction();
        if (operatorIndex > -1) {
            doMath(operatorIndex);
        } else {
            addition = false;
        }
    }
    return strtod(equationVector[0].value.c_str(), NULL);



    //cout << correctedEquationString << endl;
    //cout << findOperatorMultiplicationDivision(correctedEquationString) << endl;
    //cout << findOperatorAdditionSubtraction(correctedEquationString) << endl;
    //int operatorIndex = findOperatorAdditionSubtraction(equationList);
    //cout << operatorIndex << endl;
}

string Calculator::correctInputString(string equationString) {
    vector<char> validCharacters {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '+', '-', '*', '/', '^',
                                  'r', 'o', 't'};
    string correctedEquationString;
    for (unsigned int i = 0; i < equationString.size(); ++i) {
        if (equationString[i] != ' ') {
            if (find(validCharacters.begin(), validCharacters.end(), equationString[i]) != validCharacters.end()) {
                correctedEquationString += equationString[i];
            } else {
                return "";
            }
        }

    }
    return correctedEquationString;
}

int Calculator::findOperatorRootPow() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].value == "^" || equationVector[i].value == "root") {
            return i;
        }
    }
    return -1;
}

int Calculator::findOperatorMultiplicationDivision() {
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

vector<EquationElement> Calculator::parseEquationString(string equationString){
    vector<EquationElement> result;
    vector<string> digits {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."};
    //vector<string> operators {"+", "-", "*", "/", "^"};
    string digitsOfNumber;
    string operatorSign;
    for (int i = 0; i < equationString.size(); ++i) {
        char characterFromString = equationString[i];
        bool isNumber = find(digits.begin(), digits.end(), string(1, characterFromString)) != digits.end();
        //bool isOperator = find(operators.begin(), operators.end(), string(1, characterFromString)) != operators.end();
        if (isNumber) {
            if (operatorSign != "") {
                EquationElement character(operatorSign, false);
                result.push_back(character);
                operatorSign = "";
            }
            digitsOfNumber += characterFromString;
        } else {
            if (digitsOfNumber != "") {
                EquationElement character(digitsOfNumber, true);
                result.push_back(character);
                digitsOfNumber = "";
            }
            operatorSign += characterFromString;
        }
        if (i == equationString.size() - 1) {
            if (digitsOfNumber == "") {
                EquationElement character(operatorSign, false);
                result.push_back(character);
            } else {
                EquationElement character(digitsOfNumber, true);
                result.push_back(character);
            }
        }
    }
    return result;
}

void Calculator::doMath(int index) {
//    for(EquationElement element: equationVector){
//        element.print();
//    }

    string stringBeforeOperator = equationVector[index-1].value;
    string stringAfterOperator = equationVector[index+1].value;
    double numberBeforeOperator = strtod(stringBeforeOperator.c_str(), NULL);
    double numberAfterOperator = strtod(stringAfterOperator.c_str(), NULL);
    double result = 0.0;

    //cout << stringBeforeOperator << " " << stringAfterOperator << endl;
    string operationString = equationVector[index].value;

    if(operationString == "*") {
        result = numberBeforeOperator * numberAfterOperator;
    } else if(operationString == "+"){
        result = numberBeforeOperator + numberAfterOperator;
    }  else if(operationString == "-"){
        result = numberBeforeOperator - numberAfterOperator;
    }  else if(operationString == "/"){
        result = numberBeforeOperator / numberAfterOperator;
    } else if(operationString == "^"){
        result = pow(numberBeforeOperator, numberAfterOperator);
    }
    equationVector[index-1].value = to_string(result);
    equationVector.erase(equationVector.begin() + index, equationVector.begin() + index+2);

    //cout << result;
    //for(EquationElement element : equationVector){
    //    element.print();
    //}
}





