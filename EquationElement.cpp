#include "EquationElement.h"

EquationElement::EquationElement(string s, bool b){
    value = s;
    isNumber = b;
}

string EquationElement::getValue() {
    return value;
}

void EquationElement::setValue(string value) {
    this->value = value;
}

bool EquationElement::getIsNumber() {
    return isNumber;
}

void EquationElement::setIsnumber(bool isNumber) {
    this->isNumber = isNumber;
}


