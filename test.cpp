#include <iostream>

using namespace std;

int main() {
  int counter = 0;
  int carr[3] = {3, 4, 0};
  for (; carr[counter++] != 0;)
    ;
  cout << counter;
}