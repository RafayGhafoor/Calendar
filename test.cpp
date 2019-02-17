#include <algorithm>
#include <iostream>

using namespace std;

struct test {
  int x;
};

int getActs(test **&calendar) {
  int act_count = 0;

  while (calendar[act_count])
    act_count++;

  return act_count;
}

void resizeActs(test **&calendar) {

  int size = getActs(calendar);

  // Change size to 2
  test **ptr = new test *[size + 2];
  copy(calendar, calendar + size, ptr);
  delete[] calendar;
  calendar = nullptr;
  calendar = ptr;
}

int main() {
  // test arguments 1,2,4,7
  test **ptr = new test *[1];

  ptr[0] = new test;
  ptr[0]->x = 3;

  resizeActs(ptr);
  ptr[1] = new test;
  ptr[1]->x = 4;

  resizeActs(ptr);
  ptr[2] = new test;
  ptr[2]->x = 5;
  resizeActs(ptr);
  cout << ptr[8];
}