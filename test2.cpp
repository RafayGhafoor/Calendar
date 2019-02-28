#include <iostream>

using namespace std;

struct test
{
    int t;
};

int main()
{
    test abc;
    test *ptr1 = &abc;
    test **ptr = &ptr1;
    ptr[0]->t = 05;
    cout << ptr[0]->t << endl;
}