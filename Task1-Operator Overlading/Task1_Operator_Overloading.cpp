#include<iostream>
using namespace std;

struct Complex
    {
        double real;
        double imag;

    };

Complex operator+(const Complex& lhs, const Complex& rhs)
{
    Complex result;
    result.real = lhs.real + rhs.real;
    result.imag = lhs.imag + rhs.imag;
    return result;
}
Complex operator-(const Complex& lhs, const Complex& rhs)
{
    Complex result;
    result.real = lhs.real - rhs.real;
    result.imag = lhs.imag - rhs.imag;
    return result;
}
Complex operator*(const Complex& lhs, const Complex& rhs)
{
    Complex result;
    result.real = lhs.real * rhs.real - lhs.imag * rhs.imag;
    result.imag = lhs.real * rhs.imag + lhs.imag * rhs.real;
    return result;
}
Complex operator/(const Complex& lhs, const Complex& rhs)
{
    Complex result;
    double denominator = rhs.real * rhs.real + rhs.imag * rhs.imag;
    result.real = (lhs.real * rhs.real + lhs.imag * rhs.imag) / denominator;
    result.imag = (lhs.imag * rhs.real - lhs.real * rhs.imag) / denominator;
    return result;
}

Complex operator-(const Complex& c)
{
    Complex result;
    result.real = -c.real;
    result.imag = -c.imag;
    return result;
}

Complex& operator+=(Complex& lhs, const Complex& rhs)
{
    lhs.real += rhs.real;
    lhs.imag += rhs.imag;
    return lhs;
}
Complex& operator-=(Complex& lhs, const Complex& rhs)
{
    lhs.real -= rhs.real;
    lhs.imag -= rhs.imag;
    return lhs;
}

// Prefix increment and decrement operators for Complex numbers
Complex& operator++(Complex& c)
{
    c.real += 1;
    return c;
}
Complex& operator--(Complex& c)
{
    c.real -= 1;
    return c;
}
// Postfix increment and decrement operators for Complex numbers
Complex operator++(Complex& c, int)
{ 
    Complex temp = c;
    ++c;
    return temp;
}
Complex operator--(Complex& c, int)
{ 
    Complex temp = c;
    --c;
    return temp;
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
    return (lhs.real == rhs.real) && (lhs.imag == rhs.imag);
}
bool operator!=(const Complex& lhs, const Complex& rhs)
{
    return !(lhs == rhs);
}

int main()
{
    //1-Create two complex numbers

    // Member-wise assignment
    Complex x ;
    x.real = 3;
    x.imag = 4;
    // Aggregate initialization
    Complex y = {1, -2} ;

    cout << "Complex number x: " << x.real << " + " << x.imag << "i" << endl;
    cout << "Complex number y: " << y.real << " + " << y.imag << "i" << endl;

    //2-Add two complex numbers using overloaded operator
    Complex sum = x + y;
    cout << "Sum of x and y: " << sum.real << " + " << sum.imag << "i" << endl;
    //3-Subtract two complex numbers using overloaded operator
    Complex subtract = x - y;
    cout << "Subtraction of x and y: " << subtract.real << " + " << subtract.imag << "i" << endl;
    //4-Multiply two complex numbers using overloaded operator
    Complex multiply = x * y;
    cout << "Multiplication of x and y: " << multiply.real << " + " << multiply.imag << "i" << endl;
    //5-Divide two complex numbers using overloaded operator
    Complex divide = x / y;
    cout << "Division of x and y: " << divide.real << " + " << divide.imag << "i" << endl;

    // Negation of a complex number using overloaded operator
    Complex negative = -x;
    cout << "Negation of x: " << negative.real << " + " << negative.imag << "i" << endl;
    cout << "Real: " << negative.real << endl;
    cout << "Imaginary: " << negative.imag << endl;

    // Compound assignment using overloaded operator
    x += y;
    cout << "After += :" << endl;
    cout << "Real: " << x.real << endl;
    cout << "Imaginary: " << x.imag << endl;

    x -= y;
    cout << "After -= :" << endl;
    cout << "Real: " << x.real << endl;
    cout << "Imaginary: " << x.imag << endl;

    // Prefix increment and decrement using overloaded operators
    ++x;
    cout << "After incrementing x: "<< x.real << " + " << x.imag << "i" << endl;
    --x;
    cout << "After decrementing x: "<< x.real << " + " << x.imag << "i" << endl;

    // Postfix increment and decrement using overloaded operators
    Complex old = x++;
    cout << "Old real: " << old.real << endl;
    cout << "New real: " << x.real << endl;

    Complex old2 = x--;
    cout << "Old real: " << old2.real << endl;
    cout << "New real: " << x.real << endl;

    // Comparison using overloaded operator
    cout << "Are x and y equal? " << (x == y ? "Yes" : "No") << endl;
    cout << "Is x not equal to y? " << (x != y ? "Yes" : "No") << endl;
    
    return 0;
}