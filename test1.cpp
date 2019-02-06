#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream fin("test.txt");
    int day, month;
    fin >> day;
    cout << day;
}