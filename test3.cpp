#include <cstring>
#include <fstream>
#include <iostream>

using std::cout;

struct activity {
  int month, day, start_time, end_time;
  float priority;
  char *user_id, *title;
};

// http://thedeepbluecpp.blogspot.com/2014/01/rule-2-make-all-type-conversions.html

// Type conversions should be isolated in their own line, which should consist
// only of the assignment of the result of the type conversion to a variable of
// the target type.

// https://stackoverflow.com/questions/14067153/are-uintptr-t-and-size-t-same?noredirect=1&lq=1

// http://web.archive.org/web/20140828142605/http://www.codeproject.com/Articles/60082/About-size_t-and-ptrdiff_t

const int DAYS_IN_MONTHS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// http://blog.slickedit.com/2007/11/c-tips-pointers-and-memory-management/

void initCal(activity *****&calendar) {
  /* Initializes the calendar having the following format:
Months as a base for pointers containing quad-pointers; pointing towards
> Days > Hours > Activities > Activites Container.
The activities pointer is initially set to 10 i.e., should be able to point
towards 10 activities, in the beginning.

Constants Representation (in loops:
12 - Number of Months
24 - Number of Hours
10 - Number of Pointers for activities, initially
*/

  // Days in months of 2019, used subsequently for the allocation of days
  // pointers and their deallocation; helps keeping track of the days in months
  // and wherever (time in hours > activities > activites container) they point
  // will always be the ith index of DAYS_IN_MONTHS

  for (int i = 0; i < 12; i++) {
    calendar[i] = new activity ***[DAYS_IN_MONTHS[i]];

    for (int j = 0; j < DAYS_IN_MONTHS[i]; j++) {
      calendar[i][j] = new activity **[24];

      for (int k = 0; k < 24; k++)
        calendar[i][j][k] = new activity *[1]();
    }
  }
  calendar[0][0][0][0] = new activity;
}

// void delCal(activity *****&calendar) {
//   // A garbage cleaner function for the memory allocated by the calendar.

//   // | The grantation of rights comes with a responsibility to bear. Treat
//   // pointers with the respect you would treat a firearm — and you may not
//   find
//   // yourself shot in your own foot.| #1

//   for (int i = 0; i < 12; i++) {
//     for (int j = 0; j < DAYS_IN_MONTHS[i]; j++) {
//       for (int k = 0; k < 24; k++) {
//         for (int l = 0; k < getActivities(calendar[i][j][k]); l++) {
//           delete[] calendar[i][j][k][l]->user_id;
//           delete[] calendar[i][j][k][l]->title;
//         }
//         delete[] calendar[i][j][k];
//       }
//       delete[] calendar[i][j];
//     }
//     delete[] calendar[i];
//   }

//   delete[] calendar;
//   //
//   https://stackoverflow.com/questions/20509734/null-vs-nullptr-why-was-it-replaced
//   calendar = nullptr;
// }

int main() {
  // Initialize Calendar to the count of months in a year
  // std::ifstream fin("test.txt");
  activity *****calendar = new activity ****[12];
  initCal(calendar);
  // fillCal(calendar, fin);
  // saveCal(calendar);
  // delCal(calendar);
}