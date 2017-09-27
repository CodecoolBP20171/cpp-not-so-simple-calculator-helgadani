#include "Calculator.h"
#include <algorithm>

using namespace std;

double Calculator::evaluate(string equationString) {
    correctInputString(equationString);
    if (correctedEquationString.empty()) return 0;

    equationVector = parseEquationString(correctedEquationString);
    if (!isValidExpression()) return 0;

    doMath();
    return strtod(equationVector[0].value.c_str(), NULL);
}

void Calculator::correctInputString(string equationString) {
    for (char character : equationString) {
        if (character != ' ') {
            if (find(validCharacters.begin(), validCharacters.end(), character) != validCharacters.end()) {
                correctedEquationString += character;
            } else {
                correctedEquationString.clear();
                break;
            }
        }
    }
}

bool Calculator::isValidExpression(){
    for (EquationElement element : equationVector) {
        if (element.isNumber) {
            int floatPoints = 0;
            for (char character : element.value) character == '.' ? floatPoints += 1 : floatPoints += 0;
            if (floatPoints > 1) return false;
        } else {
            if (!(find(validOperators.begin(), validOperators.end(), element.value) != validOperators.end())) return false;
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
        if (equationVector[i].value == "/" || equationVector[i].value == "/-") return i;
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
    string digitsOfNumber;
    string operatorSign;

    for (int i = 0; i < equationString.size(); ++i) {
        char characterFromString = equationString[i];
        bool isNumber = find(validDigits.begin(), validDigits.end(), string(1, characterFromString)) != validDigits.end();

        if (isNumber) {
            if (!operatorSign.empty()) {
                EquationElement character(operatorSign, false);
                result.push_back(character);
                operatorSign.clear();
            }
            digitsOfNumber += characterFromString;
        } else {
            if (!digitsOfNumber.empty()) {
                EquationElement character(digitsOfNumber, true);
                result.push_back(character);
                digitsOfNumber.clear();
            }
            operatorSign += characterFromString;
        }

        if (i == equationString.size() - 1) {
            if (digitsOfNumber.empty()) {
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
    double numberBeforeOperator = strtod(equationVector[index-1].value.c_str(), NULL);
    double numberAfterOperator = strtod(equationVector[index+1].value.c_str(), NULL);
    string operationString = equationVector[index].value;
    double result;

    if (operationString == "root") {
        // A negatív számoknak nincsen tört, valamint páros gyökük.
        if (numberAfterOperator < 0 && ((int) numberBeforeOperator % 2 == 0 || numberBeforeOperator - (int) numberBeforeOperator != 0)) throw std::logic_error ("What the hell do you want??");
            // Negatív számok negatív egész gyökének számítása.
        else if (numberBeforeOperator < 0 && numberBeforeOperator - (int) numberBeforeOperator == 0) result = 0 - pow(abs(numberAfterOperator), 1/numberBeforeOperator);
        else result = pow(numberAfterOperator, 1/numberBeforeOperator);
    }
    else if (operationString == "^") {
        // A negatív számoknak nincsen tört hatványuk, valamint a 0-nak nincsen 0-dik hatványa.
        if ((numberBeforeOperator < 0 && numberAfterOperator - (int) numberAfterOperator != 0) ||
            (numberBeforeOperator == 0 && numberAfterOperator == 0)) throw std::logic_error ("What the hell do you want??");
        else result = pow(numberBeforeOperator, numberAfterOperator);
    }
    else if (operationString == "/") {
        if (numberAfterOperator == 0) throw std::overflow_error("Divide by zero exception");
        else result = numberBeforeOperator / numberAfterOperator;
    }
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





