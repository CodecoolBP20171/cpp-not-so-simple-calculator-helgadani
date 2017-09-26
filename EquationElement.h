//
// Created by eros on 25/09/17.
//

#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_EQUATIONELEMENT_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_EQUATIONELEMENT_H

#include <iostream>
using namespace std;

class EquationElement {
public:
    string value;
    bool isNumber;
    EquationElement(string s, bool isNumber);
    void print();
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_EQUATIONELEMENT_H
