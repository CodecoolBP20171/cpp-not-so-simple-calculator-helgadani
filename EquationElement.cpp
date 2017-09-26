//
// Created by eros on 25/09/17.
//

#include "EquationElement.h"

EquationElement::EquationElement(string s, bool b){
    value = s;
    isNumber = b;
}

void EquationElement::print() {
    cout << "value: " << value << "\tisNumber: " << isNumber << endl;
}


