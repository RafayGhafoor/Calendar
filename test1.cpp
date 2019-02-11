#include <iostream>

using namespace std;

int main()
{
  int **t = new int *[5];
  if (t[0] == nullptr)
    cout << "YES";
}