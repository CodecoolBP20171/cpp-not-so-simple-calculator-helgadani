#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_EQUATIONELEMENT_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_EQUATIONELEMENT_H

#include <iostream>

using namespace std;

class EquationElement {
private:
    string value;
    bool isNumber;
public:
    EquationElement(string value, bool isNumber);
    string getValue();
    bool getIsNumber();
    void setValue(string value);
    void setIsnumber(bool isNumber);
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_EQUATIONELEMENT_H
