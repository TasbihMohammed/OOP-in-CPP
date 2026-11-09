/* Encapsulation in C++ : -wrapping up of data and information under a single unit
                          -binding together the data and functions that manipulate them */
/* Abstraction in C++ :  -displaying only the relevant attributes of objects and hides the unnecessary details*/

// Calculator using OOP:
#include <iostream>
using namespace std;
class Calculator
{
    // private members of the class
    // Note: private members can be variables or functions
    private:
    float _PrevResult=0;
    float _LastNumber=0;
    string _LastOperation = "Clear";
    float _Result=0;

    bool _IsZero(float number)
    {
        return number == 0;
    }

    public:
    void Add(float Number)
    {
        _PrevResult = _Result;
        _LastNumber = Number;
        _LastOperation = "Add";
        _Result += Number;
    }
    void Subtract(float Number)
    {
        _PrevResult = _Result;
        _LastNumber = Number;
        _LastOperation = "Subtract";
        _Result -= Number;
    }
    void Multiply(float Number)
    {
        _PrevResult = _Result;
        _LastNumber = Number;
        _LastOperation = "Multiply";
        _Result *= Number;
    }
    void Divide(float Number)
    {
        if (_IsZero(Number))
        {
            Number = 1;
        }
        _PrevResult = _Result;
        _LastNumber = Number;
        _LastOperation = "Divide";
        _Result /= Number;
    }
    void Clear()
    {
        _PrevResult = 0;
        _LastNumber = 0;
        _LastOperation = "Clear";
        _Result = 0;
    }

    void PrintResult()
    {
        cout << "Result After " << _LastOperation << " " << _LastNumber << " is: " << _Result << endl;
    }
};

int main()
{
    Calculator calc;
    calc.Add(10);
    calc.PrintResult();
    calc.Subtract(5);
    calc.PrintResult();
    calc.Multiply(2);
    calc.PrintResult();
    calc.Divide(0);
    calc.PrintResult();
    calc.Clear();
    calc.PrintResult();
    return 0;
}