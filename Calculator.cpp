#include "Calculator.h"
#include <algorithm>

using namespace std;

double Calculator::evaluate(string equationString) {
    correctInputString(equationString);
    if (correctedEquationString.empty()) {
        cout << "nem jó" << endl;
        return 0;
    }

    equationVector = parseEquationString(correctedEquationString);
    if (!isValidExpression()) {
        cout << "ez sem jó" << endl;
        return 0;
    }

    try {
        doMath();
    } catch(overflow_error e) {
        cout << e.what();
        return 0;
    } catch (logic_error e) {
        cout << e.what();
        return 0;
    }

    return strtod(equationVector[0].getValue().c_str(), NULL);
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
    int counter = 1;
    bool isFirstElementNegative = false;
    for (EquationElement element : equationVector) {
        if (counter == 1) {
            if (element.getValue() != "-" && !element.getIsNumber()) return false;
            if (element.getValue() == "-") isFirstElementNegative = true;
        } else if (counter == equationVector.size()) {
            if (!element.getIsNumber()) return false;
        }
        if (element.getIsNumber()) {
            int floatPoints = 0;
            for (char character : element.getValue()) character == '.' ? floatPoints += 1 : floatPoints += 0;
            if (floatPoints > 1) return false;
        } else {
            if (!(find(validOperators.begin(), validOperators.end(), element.getValue()) != validOperators.end())) return false;
        }
        ++counter;
    }
    if (isFirstElementNegative) {
        equationVector[0].setValue(to_string(0 - strtod(equationVector[1].getValue().c_str(), NULL)));
        equationVector.erase(equationVector.begin() + 1);
    }
    return true;
}

int Calculator::findOperatorRootPow() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].getValue() == "^" || equationVector[i].getValue() == "root") return i;
    }
    return -1;
}

int Calculator::findOperatorMultiplicationDivision() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].getValue() == "/" || equationVector[i].getValue() == "*" ||
            equationVector[i].getValue() == "/-" || equationVector[i].getValue() == "*-" ||
            equationVector[i].getValue() == "/+" || equationVector[i].getValue() == "*+") return i;
    }
    return -1;
}

int Calculator::findOperatorAdditionSubtraction() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].getValue() == "+" || equationVector[i].getValue() == "-" ||
            equationVector[i].getValue() == "-+" || equationVector[i].getValue() == "+-") return i;
    }
    return -1;
}

vector<EquationElement> Calculator::parseEquationString(string equationString){
    vector<EquationElement> result;
    string digitsOfNumber;
    string operatorSign;

    for (int i = 0; i < equationString.size(); ++i) {
        bool isNumber = find(validDigits.begin(), validDigits.end(), string(1, equationString[i])) != validDigits.end();

        if (isNumber) {
            if (!operatorSign.empty()) {
                EquationElement character(operatorSign, false);
                result.push_back(character);
                operatorSign.clear();
            }
            digitsOfNumber += equationString[i];
        } else {
            if (!digitsOfNumber.empty()) {
                EquationElement character(digitsOfNumber, true);
                result.push_back(character);
                digitsOfNumber.clear();
            }
            operatorSign += equationString[i];
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
    double numberBeforeOperator = strtod(equationVector[index-1].getValue().c_str(), NULL);
    double numberAfterOperator = strtod(equationVector[index+1].getValue().c_str(), NULL);
    double result;
    string operationString = equationVector[index].getValue();

    if (operationString == "root") result = pow(numberAfterOperator, 1/numberBeforeOperator);
    else if (operationString == "^") {
        if (numberBeforeOperator < 0 && numberAfterOperator - (int) numberAfterOperator != 0) throw std::logic_error ("What the hell do you want??");
        else result = pow(numberBeforeOperator, numberAfterOperator);
    }

    else if (operationString == "/" || operationString == "/+") {
        if (numberAfterOperator == 0) throw std::overflow_error("Divide by zero exception");
        else result = numberBeforeOperator / numberAfterOperator;
    }
    else if (operationString == "/-") result = numberBeforeOperator / (0-numberAfterOperator);
    else if (operationString == "*" || operationString == "*+") result = numberBeforeOperator * numberAfterOperator;
    else if (operationString == "*-") result = numberBeforeOperator * (0-numberAfterOperator);
    else if (operationString == "+") result = numberBeforeOperator + numberAfterOperator;
    else if (operationString == "-" || operationString == "+-" ||
            operationString == "-+") result = numberBeforeOperator - numberAfterOperator;
    else result = 0;

    equationVector[index-1].setValue(to_string(result));
    equationVector.erase(equationVector.begin() + index, equationVector.begin() + index+2);
}





