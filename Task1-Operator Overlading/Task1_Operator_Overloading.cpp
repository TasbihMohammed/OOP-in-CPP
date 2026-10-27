#include<iostream>
#include<cmath>
// Include the <stdexcept> header for runtime_error
#include<stdexcept>
using namespace std;
// print_stars function to print a line of stars for better output formatting
void print_stars(int n)
{
    for (int i = 0; i < n; ++i)
        cout << "*";
    cout << endl;
}

/*
Note:
    Bonus features:
    1. Division by zero protection using exceptions.
    2. Mixed addition: Complex + double and double + Complex.
    3. Complex conjugate function.
    4. Complex magnitude function.
*/

struct Complex
    {
        double real;
        double imag;
    };

// (const) prevents modifying the Complex object through this reference.
// ( & ) means that the function takes a reference to the parameter, 
// which avoids making a copy of the parameter and can improve performance for large objects.
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
    double denominator = pow(rhs.real, 2) + pow(rhs.imag, 2);
    // Check for division by zero and throw an exception if the denominator is zero.(bonus feature)
    if (denominator == 0)
    {
        throw runtime_error("Division by zero");
    }
    result.real = (lhs.real * rhs.real + lhs.imag * rhs.imag) / denominator;
    result.imag = (lhs.imag * rhs.real - lhs.real * rhs.imag) / denominator;
    return result;
}

// Negation operator for Complex numbers
Complex operator-(const Complex& c)
{
    Complex result;
    result.real = -c.real;
    result.imag = -c.imag;
    return result;
}

// ( & ) "after Complex" means that the function returns a reference to the Complex object,
// which allows for chaining of operations and avoids making a copy of the object.
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
// (int) is a dummy parameter to differentiate between prefix and postfix versions of the operator.
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

// (ostream) is the output stream class in C++ used for output operations,
// and (istream) is the input stream class used for input operations.
ostream& operator<<(ostream& os, const Complex& c)
{
    if (c.imag >= 0)
        os << c.real << " + " << c.imag << "i";
    else
        os << c.real << " - " << -c.imag << "i";
    return os;
}
istream& operator>>(istream& is, Complex& c)
{
    is >> c.real >> c.imag;
    return is;
}

// ***************************************************************************
//                         Bonus features:
// ***************************************************************************

// Mixed addition: Complex + double and double + Complex.
Complex operator+(const Complex& lhs, double rhs)
{
    Complex result;
    result.real = lhs.real + rhs;
    result.imag = lhs.imag;
    return result;
}
Complex operator+(double lhs, const Complex& rhs)
{
    Complex result;
    result.real = lhs + rhs.real;
    result.imag = rhs.imag;
    return result;
}
// Complex conjugate function
Complex conjugate(const Complex& c)
{
    Complex result;
    result.real = c.real;
    result.imag = -c.imag;
    return result;
}
// Complex magnitude function
double magnitude(const Complex& c)
{
    return sqrt(pow(c.real, 2) + pow(c.imag, 2));
}

int main()
{
    cout << "Operator Overloading in C++" << endl;
    print_stars(50); 

    //Create two complex numbers:

    // Member-wise assignment
    Complex x ;
    x.real = 3;
    x.imag = 4;
    // Aggregate initialization
    Complex y = {1, -2} ;

    cout << "Complex number x: " << x << endl;
    cout << "Complex number y: " << y << endl << endl;

    //Add two complex numbers using overloaded operator
    Complex sum = x + y;
    cout << "Sum of x and y: " << sum << endl;
    //Subtract two complex numbers using overloaded operator
    Complex subtract = x - y;
    cout << "Subtraction of x and y: " << subtract << endl;
    //Multiply two complex numbers using overloaded operator
    Complex multiply = x * y;
    cout << "Multiplication of x and y: " << multiply << endl;
    //Divide two complex numbers using overloaded operator
    Complex divide = x / y;
    cout << "Division of x and y: " << divide << endl;
    print_stars(50);

    Complex m{5, -6};
    Complex n{2, 3};
    cout << "Complex number m: " << m << endl;
    cout << "Complex number n: " << n << endl << endl;
    // Negation of a complex number using overloaded operator
    Complex negative = -m;
    cout << "Negation of m: " << negative << endl << endl;

    // Compound assignment using overloaded operator
    cout << "Compound assignment:" << endl;
    m += n;
    cout << "m after += n: " << m << endl;
    m -= n;
    cout << "m after -= n: " << m << endl;

    // Prefix increment and decrement using overloaded operators
    cout << "\nPrefix increment and decrement:" << endl;
    ++m;
    cout << "After incrementing m: "<< m << endl;
    --m;
    cout << "After decrementing m: "<< m << endl;

    // Test postfix increment and decrement.
    cout << "\nPostfix increment and decrement:" << endl;
    Complex oldValue = m++;
    cout << "Value returned by m++: " << oldValue << endl;
    cout << "New value after m++: " << m << endl ;
    
    oldValue = m--;
    cout << "Value returned by m--: " << oldValue << endl;
    cout << "New value after m--: " << m << endl << endl;

    // Comparison using overloaded operator
    cout << "Are m and n equal? " << (m == n ? "Yes" : "No") << endl;
    cout << "Is m not equal to n? " << (m != n ? "Yes" : "No") << endl;
    print_stars(50);

    cout<< "Bonus features:" << endl << endl;
    Complex j = {3, 4};
    Complex k = {0, 0};
    cout << "Complex number j: " << j << endl;
    cout << "Complex number k: " << k << endl << endl;

    cout << "1- Division by zero protection using exceptions:" << endl; 
    cout << "Divide j by k (which is zero), Resulting in an exception:" << endl;
    try
    {
        Complex result = j / k;
        cout << result << endl;
    }
    catch (const runtime_error& e)
    {
        cerr << e.what() << endl;
    }
    
    cout << "\n2- Mixed addition: Complex + double and double + Complex:" << endl;
    Complex m1 = j + 5.0;
    cout << "Result of mixed addition (add 5.0 to j): " << m1 << endl;
    Complex m2 = 5.0 + j;
    cout << "Result of mixed addition (add j to 5.0): " << m2 << endl;

    cout << "\n3- Complex conjugate function:" << endl;
    Complex conj = conjugate(j);
    cout << "Conjugate of j: " << conj << endl;

    cout << "\n4- Complex magnitude function:" << endl;
    double mag = magnitude(j);
    cout << "Magnitude of j: " << mag << endl;
    print_stars(50);

    // Test the input operator.
    cout << "\nTest the input operator (>>):" << endl;
    Complex input;
    cout << "Enter real and imaginary parts: ";
    cin >> input;
    cout << "You entered: " << input << endl;

    return 0;
}