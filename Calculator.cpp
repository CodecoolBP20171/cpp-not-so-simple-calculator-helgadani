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
    int counter = 1;
    for (EquationElement element : equationVector) {
        if (counter == 1) {
            if (element.value != "-" && !element.isNumber) return false;
        } else if (counter == equationVector.size()) {
            if (!element.isNumber) return false;
        }
        if (element.isNumber) {
            int floatPoints = 0;
            for (char character : element.value) character == '.' ? floatPoints += 1 : floatPoints += 0;
            if (floatPoints > 1) return false;
        } else {
            if (!(find(validOperators.begin(), validOperators.end(), element.value) != validOperators.end())) return false;
        }
        ++counter;
    }
    return true;
}

vector<double> Calculator::findNumbers(int index) {
    double numberBeforeOperator;
    double numberAfterOperator;

    if (index == 0) {
        numberBeforeOperator = 0;
        numberAfterOperator = strtod(equationVector[index+1].value.c_str(), NULL);
    } else if (index == equationVector.size()-1) {
        numberBeforeOperator = strtod(equationVector[index-1].value.c_str(), NULL);
        numberAfterOperator = 0;
    } else {
        numberBeforeOperator = strtod(equationVector[index-1].value.c_str(), NULL);
        numberAfterOperator = strtod(equationVector[index+1].value.c_str(), NULL);
    }
    return vector<double> {numberBeforeOperator, numberAfterOperator};
}

int Calculator::findOperatorRootPow() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].value == "^" || equationVector[i].value == "root") return i;
    }
    return -1;
}

int Calculator::findOperatorMultiplicationDivision() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].value == "/" || equationVector[i].value == "*" ||
            equationVector[i].value == "/-" || equationVector[i].value == "*-" ||
            equationVector[i].value == "/+" || equationVector[i].value == "*+") return i;
    }
    return -1;
}

int Calculator::findOperatorAdditionSubtraction() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].value == "+" || equationVector[i].value == "-" ||
            equationVector[i].value == "-+" || equationVector[i].value == "+-") return i;
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
        if (operatorIndex > -1) {
            vector<double> numbers = findNumbers(operatorIndex);
            doOperation(operatorIndex, numbers[0], numbers[1]);
        }
        else operatorPrecedence1 = false;
    }

    while (operatorPrecedence2) {
        int operatorIndex = findOperatorMultiplicationDivision();
        if (operatorIndex > -1) {
            vector<double> numbers = findNumbers(operatorIndex);
            doOperation(operatorIndex, numbers[0], numbers[1]);
        }
        else operatorPrecedence2 = false;
    }

    while (operatorPrecedence3) {
        int operatorIndex = findOperatorAdditionSubtraction();
        if (operatorIndex > -1) {
            vector<double> numbers = findNumbers(operatorIndex);
            doOperation(operatorIndex, numbers[0], numbers[1]);
        }
        else operatorPrecedence3 = false;
    }
}

void Calculator::doOperation(int index, double numberBeforeOperator, double numberAfterOperator) {

    double result;
    string operationString = equationVector[index].value;

    if (operationString == "root") result = pow(numberAfterOperator, 1/numberBeforeOperator);
    else if (operationString == "^") result = pow(numberBeforeOperator, numberAfterOperator);
    else if (operationString == "/" || operationString == "/+") result = numberBeforeOperator / numberAfterOperator;
    else if (operationString == "/-") result = numberBeforeOperator / (0-numberAfterOperator);
    else if (operationString == "*" || operationString == "*+") result = numberBeforeOperator * numberAfterOperator;
    else if (operationString == "*-") result = numberBeforeOperator * (0-numberAfterOperator);
    else if (operationString == "+") result = numberBeforeOperator + numberAfterOperator;
    else if (operationString == "-" ||
            operationString == "+-" ||
            operationString == "-+") result = numberBeforeOperator - numberAfterOperator;
    else result = 0;


    if (index != 0) {
        equationVector[index-1].value = to_string(result);
        equationVector.erase(equationVector.begin() + index, equationVector.begin() + index+2);
    } else {
        equationVector[index].value = to_string(result);
        equationVector.erase(equationVector.begin() + index);
    }

    //cout << result;
    //for(EquationElement element : equationVector){
    //    element.print();
    //}
}





