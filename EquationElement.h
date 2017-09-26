#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_EQUATIONELEMENT_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_EQUATIONELEMENT_H

#include <iostream>

using namespace std;

class EquationElement {
public:

    string value;
    bool isNumber;

    EquationElement(string value, bool isNumber);

    void print();
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_EQUATIONELEMENT_H
