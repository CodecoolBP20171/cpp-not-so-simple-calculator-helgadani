#ifndef CALCULATOR_TESTER_HPP
#define CALCULATOR_TESTER_HPP
#include <iostream>
#include <string>
#include "Calculator.h"

class Tester {
public:
    void run()
    {
        failedTests = 0;
        // Level 0
        TestAddition();
        TestAddition2();
        TestSubtraction();
        TestMultiplication();
        TestDivision();
        TestDivision2();
        TestFormulaWithSpaces();

        // Level 1
        TestRoot();
        TestRoot1();
        TestRoot2();
        TestPow();
        TestFractional();
        TestComplicatedFormula_noBrackets();
        TestComplicatedFormula_root();
        TestComplicatedFormula_rootAndPower();
        TestErroneousFormula_rootTypoNoBrackets();
        TestErroneousFormula_rootTypoNoBrackets2();

/*
        // Boss fight
        TestComplicatedFormula_brackets();
        TestComplicatedFormula_bracketsBeforeRoot();
        TestComplicatedFormula_bracketsAfterRoot();
        TestErroneousFormula_missingOpeningBracket();
        TestErroneousFormula_missingClosingBracket();
        TestErroneousFormula_missing_param();
*/
        evaluateTestOutcomes();
    }

private:
    int failedTests;

    void TestAddition()
    {
        Calculator c;
        string input = "10+2";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(12, result);
    }

    void TestAddition2()
    {
        Calculator c;
        string input = "-10+2";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(-8, result);
    }

    void TestSubtraction()
    {
        Calculator c;
        string input = "10-2";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(8, result);
    }

    void TestMultiplication()
    {
        Calculator c;
        string input = "3*2";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(6, result);
    }

    void TestDivision()
    {
        Calculator c;
        string input = "10/3";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(3.3, result, 0.05);
    }

    void TestDivision2()
    {
        Calculator c;
        string input = "10/0";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(0, result, 0.05);
    }

    void TestFormulaWithSpaces()
    {
        Calculator c;
        string input = " 10 / 3*2 +   8 ";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(14.7, result, 0.05);
    }

    void TestPow()
    {
        Calculator c;
        string input = " 10^3";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(1000, result);
    }

    void TestRoot()
    {
        Calculator c;
        string input = "2root25";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(5, result);
    }

    void TestRoot1()
    {
        Calculator c;
        string input = "0root25";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(0, result);
    }

    void TestRoot2()
    {
        Calculator c;
        string input = "root25";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(0, result);
    }

    void TestFractional()
    {
        Calculator c;
        string input = "2.3+2.7";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(5, result);
    }

    void TestComplicatedFormula_noBrackets()
    {
        Calculator c;
        string input = "12+20*3-50/2+3";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(50, result);
    }

    void TestComplicatedFormula_root()
    {
        Calculator c;
        string input = "12+2*2root25+3";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(25, result);
    }

    void TestComplicatedFormula_rootAndPower()
    {
        Calculator c;
        string input = "12+2*2root25+10^4+6-3";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(10025, result);
    }

    void TestErroneousFormula_rootTypoNoBrackets()
    {
        Calculator c;
        // calculator prints an error msg and returns with 0
        string input = "12+2*2rrot25+10^4+6-3";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(0, result);
    }

    void TestErroneousFormula_rootTypoNoBrackets2()
    {
        Calculator c;
        // calculator prints an error msg and returns with 0
        string input = "-12+2*-+2root-25+10^4+6-3";
        double result = c.evaluate(input);
        cout << input << " = " << result << ". ";
        checkResult(0, result);
    }

    void TestComplicatedFormula_brackets()
    {
        Calculator c;
        double result = c.evaluate("2root(22+(33-2root25+14)*2+(5-2))");
        checkResult(10.4403d, result, 0.01d);
    }

    void TestComplicatedFormula_bracketsBeforeRoot()
    {
        Calculator c;
        double result = c.evaluate("((2+2)*2-6)root25+10^4+6-3");
        checkResult(10008, result);
    }

    void TestComplicatedFormula_bracketsAfterRoot()
    {
        Calculator c;
        double result = c.evaluate("2root((10-5)*4/(2+80))");
        checkResult(0.493, result, 0.01);
    }

    void TestErroneousFormula_missingOpeningBracket()
    {
        Calculator c;
        double result = c.evaluate("(2+2)*2-6)root25+10^4+6-3");
        checkResult(0, result);
    }

    void TestErroneousFormula_missingClosingBracket()
    {
        Calculator c;
        double result = c.evaluate("((2+2)*2-6root25+10^4+6-3");
        checkResult(0, result);
    }

    void TestErroneousFormula_missing_param()
    {
        Calculator c;
        double result = c.evaluate("12+2*root25+10^4+6-3");
        checkResult(0, result);
    }

    void checkResult(const double expected, const double actual, const double threshold = 0.0d)
    {
        if( actual >= expected - threshold &&
            actual <= expected + threshold )
        {
            cout << "Test ran OK." << endl;
        }else{
            cout << "Invalid result! Expected: " << expected << " actual: " << actual << endl;
            ++failedTests;
        }
    }

    void evaluateTestOutcomes()
    {
        if(0 != failedTests){
            cout << failedTests << " tests failed." << endl;
        }else{
            cout << "All tests passed!" << endl;
        }
    }
};


#endif //CALCULATOR_TESTER_HPP
