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
    void setValue(string value);
    bool getIsNumber();
    void setIsnumber(bool isNumber);
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_HELGADANI_EQUATIONELEMENT_H
