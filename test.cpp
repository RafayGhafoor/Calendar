#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    double arr[] = {4.3, 4.8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    cout << arr[findMax(arr, size)];
}