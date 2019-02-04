#include <iostream>

using namespace std;

int getSize(int **&calendar, int month, int day, int hour) {
  int allocated_hours = 0;

  for (; calendar[month][day][allocated_hours]; allocated_hours++)
    ;

  return allocated_hours;
}

int main() {
  int **ptr = new int *[10]();
  int x = 3, y = 4;
  ptr[0] = &x;

  ptr[1] = &y;

  cout << getSize(ptr, 0);

  delete[] ptr;

  ptr = 0;
}