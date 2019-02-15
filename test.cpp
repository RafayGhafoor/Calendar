#include <algorithm>
#include <iostream>

using namespace std;

void Resize(int **&calendar, const int &size) {
  // Resizes the pointers of the activity
  int **ptr = new int *[size + 1];
  copy(calendar, calendar + size, ptr);
  delete[] calendar;
  calendar = ptr;
}

// can't use const here
// https://stackoverflow.com/questions/16390294/conversion-from-int-to-const-int
int getActivities(int **&calendar) {
  // Returns count of the allocated pointers;   used for checking activities
  // existence.
  // Usage Example: getActivities(calendar[0][0][0])
  cout << "test";
  int act_count = 0;

  while (calendar[act_count])
    act_count++;

  return act_count;
}

int main() {
  int **arr = new int *[8];
  int a = 2, b = a, c = a, d = a;
  cout << getActivities(arr);
}