#include<iostream>
using namespace std;
int main()
{
{
    // Question 1: What is the output?
    int x = 10;
    int* p = &x;
    int** q = &p;
    **q = 20;
    *p += 5;
    cout <<"Question 1 Answer: ";
    cout << x << " " << *p << " " << **q;
}

{
    // Question 2: What is the output?
    int a = 5, b = 10;
    int* p = &a;
    int& r = b;
    *p = r;
    r = *p + 3;
    p = &b;
    *p += a;
    cout<<"\nQuestion 2 Answer: ";
    cout << a << " " << b;
}

{
    // Question 3: What is the output?
    int arr[] = {2, 4, 6, 8, 10};
    int* p = arr;
    cout << "\nQuestion 3 Answer: ";
    cout << *p++ << " ";
    cout << ++*p << " ";
    cout << *++p << " ";
    cout << *(p + 2);
}

{
    // Question 4: What is the output?
    int x = 7;
    int& a = x;
    int* p = &a;
    int& b = *p;
    b++;
    *p += 2;
    a *= 2;
    cout << "\nQuestion 4 Answer: ";
    cout << x;
}

    


    return 0;
}