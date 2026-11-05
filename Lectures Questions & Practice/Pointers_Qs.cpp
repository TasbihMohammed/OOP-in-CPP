#include<iostream>
using namespace std;
// update function for Question 5
void update(int* p, int& r)
{
    p = &r;
    *p += 5;
    r *= 2;
}
// modify function for Question 9
void modify(int*& p) {
    static int y = 50;
    p = &y;
    *p += 10;
}
int main()
{
{
    // Question 1: What is the output?
    int x = 10;
    int* p = &x;
    int** q = &p; // **q is a pointer to a pointer, which points to p, which in turn points to x
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
    cout << *p++ << " "; // ++ here increments the pointer after dereferencing, 
    // so it prints 2 and then moves to the next element
    cout << ++*p << " "; // ++ here increments the value pointed to by p (which is now 4), so it prints 5
    cout << *++p << " "; // ++ here increments the pointer first,
    // so it moves to the next element (which is 6) and then dereferences it, printing 6
    cout << *(p + 2); // here p is currently pointing to the 3rd element (6),
     // so p + 2 points to the 5th element (10), and dereferencing it prints 10
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

{
    // Question 5: What is the output
    int a = 3, b = 4;
    int* ptr = &a;
    update(ptr, b); // here, ptr is passed by value, 
    // so the function update cannot change the original pointer ptr in main.
    // However, it can modify the value of b through the reference r.
    cout << "\nQuestion 5 Answer: ";
    cout << a << " " << b << " " << *ptr;
}

{
    // Question 6: What is the output?
    int x = 10;
    int* p = &x;
    int* q = p;
    *q = 15;
    *p += 5;
    cout << "\nQuestion 6 Answer: ";
    cout << x << " " << *p << " " << *q;
}

{
    // Question 7: What is the output?
    int a = 1, b = 2, c = 3;
    int* p = &a;
    int** pp = &p;
    *pp = &b;
    **pp += c;
    p = &c;
    **pp += a + b;
    cout << "\nQuestion 7 Answer: ";
    cout << a << " " << b << " " << c;
}

{
    // Question 8: What is the output?
    int arr[] = {10, 20, 30, 40};
    int* p = arr;
    int* q = p + 2;
    *q = *p + *(p + 1);
    cout << "\nQuestion 8 Answer: ";
    cout << arr[2] << " " << *(q - 1);
}

{
    // Question 9: What is the output?
    int x = 5;
    int* p = &x;
    modify(p); // here, p is passed by reference, 
    // so the function modify can change the original pointer p in main.
    cout << "\nQuestion 9 Answer: ";
    cout << x << " " << *p;
}

{
    // Question 10: What is the output?
    int x = 4;
    int* p = &x;
    int& r = *p;
    int** pp = &p;
    int* q = &r;
    *q = 8;
    **pp += 2;
    r++;
    cout << "\nQuestion 10 Answer: ";
    cout << x;
}

{
    // Question 11: What is the output?
    int a = 3, b = 6;
    int* p = &a;
    int*& ref = p; // *&ref is a reference to the pointer p, so ref and p point to the same address
    ref = &b;
    *ref += a;
    cout << "\nQuestion 11 Answer: ";
    cout << a << " " << b;
}

    return 0;
}