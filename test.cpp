#include <algorithm>
#include <iostream>

using namespace std;

void Resize(int **&calendar, const int &size)
{
  // Resizes the pointers of the activity
  int **ptr = new int *[size + 1];
  copy(calendar, calendar + size, ptr);
  delete[] calendar;
  calendar = ptr;
}

// can't use const here
// https://stackoverflow.com/questions/16390294/conversion-from-int-to-const-int
int getActivities(int **&calendar)
{
  // Returns count of the allocated pointers;   used for checking activities
  // existence.
  // Usage Example: getActivities(calendar[0][0][0])
  int act_count = 0;

  while (calendar[act_count])
    act_count++;

  return act_count;
}

int main()
{
  int **arr = new int *[1];

  for (int i = 0; i < 10; i++)
  {
    arr[i] = new int;
    arr[i][0] = i;
    // cout << arr[i][0] << std::endl;
    Resize(arr, getActivities(arr));
    cout << arr[i][0] << std::endl;
  }
}