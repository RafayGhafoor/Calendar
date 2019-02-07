#include <cstring>
#include <iostream>

using namespace std;

bool isValidID(char userID[]) {
  /*
    Sanity check for userid.

    Following are the rules that can be generalized from the observed dataset:

    i)  UserID always starts with the string "user"
    ii) UserID will never exceed 6 characters "userDD", where D represents a
   digit iii) Digits must come after the string "user"

  */
  bool idStatus = true;
  char begin[] = "user";

  int length = strlen(userID);

  // Sanity Check for Rule No. 1
  for (int i = 0; i < 4 && idStatus; i++)
    if (begin[i] != userID[i])
      idStatus = false;

  // Sanity Check for Rule No. 2
  if (length > 6 || length < 5)
    idStatus = false;

  // Sanity Check for Rule No. 3
  for (int i = 4; i < length && idStatus; i++)
    if (userID[i] < 0 && userID[i] > 9)
      idStatus = false;

  return idStatus;
}

bool isValidMonth(int month) {
  // Sanity check for months validity (check is based upon index which will
  // always be 1 less than the month)
  if (month < 0 || month > 11)
    return false;
  return true;
}

bool isValidDay(int day) {
  // Max day size is 30 because we will be comparing against month index which
  // is (n - 1)
  if (day < 0 || day > 30)
    return false;
  return true;
}

bool isValidPeriod(int start_month, int end_month, int start_day, int end_day) {
  /*
  A period is only valid if end month will be greater than start month because
  you can't go back in time :P The end day could also not be greater than start
  day for the same reason mentioned above.
  */
  if (start_month > end_month)
    return false;

  if (start_month == end_month)
    if (start_day > end_day)
      return false;

  return true;
}
