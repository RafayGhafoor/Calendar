#include <iostream>

using std::cout;

struct duration {
  int month;
  int date;
  int time;
};

struct activity {
  char *title;
  char *userid;
  duration time;
  float priority;
};

int main() {

  // keeps track of the days, in months of year, 2019
  int days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // |Allocation takes place from here|
  // Initialize Calendar to the count of months in a year
  int *****calendar = new int ****[12];

  /*

  Constants Representation (in loops:
  12 - Number of Months
  24 - Number of Hours
  10 - Number of Pointers for activities, initially
  */

  for (int i = 0; i < 12; i++) {
    calendar[i] = new int ***[days_in_months[i]];

    for (int j = 0; j < days_in_months[i]; j++) {
      calendar[i][j] = new int **[24];
      for (int k = 0; k < 24; k++)
        calendar[i][j][k] = new int *[10];
    }
  }

  // Deallocation of the allocated arrays
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < days_in_months[i]; j++) {
      for (int k = 0; k < 24; k++)
        delete[] calendar[i][j][k];
      delete[] calendar[i][j];
    }
    delete[] calendar[i];
  }

  delete[] calendar;
}