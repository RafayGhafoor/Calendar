#include <cstring>
#include <fstream>
#include <iostream>

using std::cout;
/*
Playing with parsing of data files
*/

struct actMetaData {
  int month, day, start, end;

  float priority;

  char *user_id, *title;
};

int main() {
  // Contains the number of days in each months for year <2019>
  // int days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  // day/month, start_time, end_time, userid, actid, title, priority
  char text[] = "2 / 7, 2, 10, user89, act1300, tease the enquiry, 0.65";

  // Position (num) for keeping track of the parsed text and organizing the
  // information for the calendar

  // 0 - Month
  // 1 - Day
  // 2 - Start-Time
  // 3 - End-Time
  // 4 - User-Id
  // 5 - Title
  // 6 - Priority

  char *pch = std::strtok(text, ",/");
  while (pch != NULL) {
    cout << pch << std::endl;
    pch = std::strtok(NULL, ",/");
  }
}