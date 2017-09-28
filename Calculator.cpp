#include "Calculator.h"
#include <algorithm>

using namespace std;

double Calculator::evaluate(string equationString) {
    correctInputString(equationString);
    if (correctedEquationString.empty()) {
        cout << "Something is not correct, check your characters in your equation!" << endl;
        return 0;
    }
    equationVector = parseEquationString(correctedEquationString);
    if (!isValidExpression()) {
        cout << "Not a valid equation." << endl;
        return 0;
    }

    try {
        doMath();
    } catch(overflow_error exeption) {
        cout << exeption.what() << endl;
        return 0;
    } catch (logic_error exception) {
        cout << exception.what() << endl;
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
    int counter = 0;
    bool isPreviousBracket = false;

    for (EquationElement element : equationVector) {
        if  (counter == 0) {
            if (element.getValue() != "-" && element.getValue() != "(" && !element.getIsNumber()) return false;
            if (element.getValue() == "(") {
                //isPreviousBracket = true;
                openBracket.push_back(counter);
            }
        } else if (counter == equationVector.size() -1) {
            if (!element.getIsNumber() && element.getValue() != ")") return false;
            if (element.getValue() == ")") {
                closeBracket.push_back(counter);
            }

        } else {

        }
        ++counter;
    }
    //return openBracket == closeBracket ? true : false;



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
        if (equationVector[i].getValue() == "/" || equationVector[i].getValue() == "*") return i;
    }
    return -1;
}

int Calculator::findOperatorAdditionSubtraction() {
    for (int i = 0; i < equationVector.size(); ++i) {
        if (equationVector[i].getValue() == "+" || equationVector[i].getValue() == "-") return i;
    }
    return -1;
}

vector<EquationElement> Calculator::parseEquationString(string equationString){
    vector<EquationElement> result;
    string digitsOfNumber;
    string operatorSign;
    string bracket;
    // TODO Maybe it should be less than 100 line??
    for (int i = 0; i < equationString.size() - 1; ++i) {
        bool isNumber = find(validDigits.begin(), validDigits.end(), string(1, equationString[i])) != validDigits.end();
        bool isNextNumber = find(validDigits.begin(), validDigits.end(), string(1, equationString[i+1])) != validDigits.end();
        bool isBracket = (equationString[i] == '(' || equationString[i] == ')');
        bool isNextBracket = (equationString[i+1] == '(' || equationString[i+1] == ')');

        if (i == (equationString.size() - 2)) {
            if (isNumber) {
                digitsOfNumber += equationString[i];
                if (isNextNumber) {
                    digitsOfNumber += equationString[i+1];
                    EquationElement character(digitsOfNumber, true);
                    result.push_back(character);}
                else {
                    EquationElement character(digitsOfNumber, true);
                    result.push_back(character);
                    if (isNextBracket) {
                        bracket += equationString[i+1];
                        EquationElement lastCharacter(bracket, false);
                        result.push_back(lastCharacter);
                    } else {
                        operatorSign += equationString[i+1];
                        EquationElement lastCharacter(operatorSign, false);
                        result.push_back(lastCharacter);
                    }
                }
            } else if (isBracket) {
                bracket += equationString[i];
                EquationElement character(bracket, false);
                result.push_back(character);
                if (isNextNumber) {
                    digitsOfNumber += equationString[i+1];
                    EquationElement lastCharacter(digitsOfNumber, true);
                    result.push_back(lastCharacter);
                } else if (isNextBracket) {
                    bracket.clear();
                    bracket += equationString[i+1];
                    EquationElement lastCharacter(bracket, false);
                    result.push_back(lastCharacter);
                } else {
                    operatorSign += equationString[i+1];
                    EquationElement lastCharacter(operatorSign, false);
                    result.push_back(lastCharacter);
                }
            } else {
                operatorSign += equationString[i];
                if (!isNextNumber && !isNextBracket) {
                    operatorSign += equationString[i+1];
                    EquationElement character(operatorSign, false);
                    result.push_back(character);
                } else {
                    EquationElement character(operatorSign, false);
                    result.push_back(character);
                    if (isNextNumber) {
                        digitsOfNumber += equationString[i+1];
                        EquationElement lastCharacter(digitsOfNumber, true);
                        result.push_back(lastCharacter);
                    } else {
                        bracket += equationString[i+1];
                        EquationElement lastCharacter(bracket, false);
                        result.push_back(lastCharacter);
                    }
                }
            }
        } else {
            if (isNumber) {
                digitsOfNumber += equationString[i];
                if (!isNextNumber) {
                    EquationElement character(digitsOfNumber, true);
                    result.push_back(character);
                    digitsOfNumber.clear();
                }
            } else if (isBracket) {
                bracket += equationString[i];
                EquationElement character(bracket, false);
                result.push_back(character);
                bracket.clear();
            } else {
                operatorSign += equationString[i];
                if (isNextNumber || isNextBracket) {
                    EquationElement character(operatorSign, false);
                    result.push_back(character);
                    operatorSign.clear();
                }
            }
        }
    }
    for (EquationElement element : result) {
        cout << element.getValue() << endl;
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
    string operationString = equationVector[index].getValue();;

    if (operationString == "root") {
        // TODO A negatív számoknak nincsen tört, valamint páros gyökük.
        if (((int) numberBeforeOperator % 2 == 0 || numberBeforeOperator - (int) numberBeforeOperator != 0) &&
            numberAfterOperator < 0) throw std::logic_error ("Operation is impossible to perform.");
            // TODO Negatív számok negatív egész gyökének számítása.
        else if (numberBeforeOperator < 0 && numberBeforeOperator - (int) numberBeforeOperator == 0) result = 0 - pow(abs(numberAfterOperator), 1/numberBeforeOperator);
        else result = pow(numberAfterOperator, 1/numberBeforeOperator);
    }
    else if (operationString == "^") {
        // TODO A negatív számoknak nincsen tört hatványuk, valamint a 0-nak nincsen 0-dik hatványa.
        if ((numberBeforeOperator < 0 && numberAfterOperator - (int) numberAfterOperator != 0) ||
            (numberBeforeOperator == 0 && numberAfterOperator == 0)) throw std::logic_error ("Operation is impossible to perform.");
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

    equationVector[index-1].setValue(to_string(result));
    equationVector.erase(equationVector.begin() + index, equationVector.begin() + index+2);
}





