#include <iostream>
#include <vector>
#include "Calculator.h"
#include <algorithm>
#include "EquationElement.h"

using namespace std;

double Calculator::evaluate(string equationString) {
    correctInputString(equationString);
    if (correctedEquationString == "") return 0;

    equationVector = parseEquationString(correctedEquationString);
    if (!isValidExpression()) return 0;
    //for(EquationElement element: equationList){
    //    element.print();
    //}
    doMath();

    return strtod(equationVector[0].value.c_str(), NULL);



    //cout << correctedEquationString << endl;
    //cout << findOperatorMultiplicationDivision(correctedEquationString) << endl;
    //cout << findOperatorAdditionSubtraction(correctedEquationString) << endl;
    //int operatorIndex = findOperatorAdditionSubtraction(equationList);
    //cout << operatorIndex << endl;
}

void Calculator::correctInputString(string equationString) {
    vector<char> validCharacters {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '+', '-', '*', '/', '^',
                                  'r', 'o', 't'};
    for (char character : equationString) {
        if (character != ' ') {
            if (find(validCharacters.begin(), validCharacters.end(), character) != validCharacters.end()) {
                correctedEquationString += character;
            } else {
                correctedEquationString = "";
                break;
            }
        }
    }
}

bool Calculator::isValidExpression(){
    for (EquationElement element : equationVector) {
        if (element.isNumber) {
            int floatPoints = 0;
            for (char character : element.value) {
                character == '.' ? floatPoints += 1 : floatPoints += 0;
            }
            if (floatPoints > 1) return false;
        } else {
            if (!(find(operators.begin(), operators.end(), element.value) != operators.end())) return false;
        }
    }
    return true;
}

int Calculator::findOperatorRootPow() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].value == "^" || equationVector[i].value == "root") return i;
    }
    return -1;
}

int Calculator::findOperatorMultiplicationDivision() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].value == "/" || equationVector[i].value == "*") return i;
    }
    return -1;
}

int Calculator::findOperatorAdditionSubtraction() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].value == "+" || equationVector[i].value == "-") return i;
    }
    return -1;
}

vector<EquationElement> Calculator::parseEquationString(string equationString){
    vector<EquationElement> result;
    //vector<string> digits {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."};
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

void Calculator::doMath() {
    while (operatorPrecedence1) {
        int operatorIndex = findOperatorRootPow();
        if (operatorIndex > -1) doOperation(operatorIndex);
        else operatorPrecedence1 = false;
    }
    while (operatorPrecedence2) {
        int operatorIndex = findOperatorMultiplicationDivision();
        if (operatorIndex > -1) doOperation(operatorIndex);
        else operatorPrecedence2 = false;
    }
    while (operatorPrecedence3) {
        int operatorIndex = findOperatorAdditionSubtraction();
        if (operatorIndex > -1) doOperation(operatorIndex);
        else operatorPrecedence3 = false;
    }
}

void Calculator::doOperation(int index) {
//    for(EquationElement element: equationVector){
//        element.print();
//    }
    double numberBeforeOperator = strtod(equationVector[index-1].value.c_str(), NULL);
    double numberAfterOperator = strtod(equationVector[index+1].value.c_str(), NULL);
    string operationString = equationVector[index].value;
    double result;

    //cout << stringBeforeOperator << " " << stringAfterOperator << endl;
    if (operationString == "root") result = pow(numberAfterOperator, 1/numberBeforeOperator);
    else if (operationString == "^") result = pow(numberBeforeOperator, numberAfterOperator);
    else if (operationString == "/") result = numberBeforeOperator / numberAfterOperator;
    else if (operationString == "*") result = numberBeforeOperator * numberAfterOperator;
    else if (operationString == "+") result = numberBeforeOperator + numberAfterOperator;
    else if (operationString == "-") result = numberBeforeOperator - numberAfterOperator;
    else result = 0;

    equationVector[index-1].value = to_string(result);
    equationVector.erase(equationVector.begin() + index, equationVector.begin() + index+2);

    //cout << result;
    //for(EquationElement element : equationVector){
    //    element.print();
    //}
}





