#include <cstring>
#include <iostream>

using namespace std;

bool isValidID(char userID[])
{
  bool idStatus = true;
  char begin[] = "user";

  int length = strlen(userID);

  if (length > 6 || length < 5)
    idStatus = false;

  for (int i = 0; i < 4 && idStatus; i++)
    if (begin[i] != userID[i])
      idStatus = false;

  for (int i = 4; i < length && idStatus; i++)
    if (userID[i] < 0 && userID[i] > 9)
      idStatus = false;

  return idStatus;
}

bool isValidMonth(int month)
{
  if (month < 0 || month > 11)
    return false;
  return true;
}

bool isValidDay(int day)
{
  // Max day size is 30 because we will be comparing against month index which
  // is (n - 1)
  if (day < 0 || day > 30)
    return false;
  return true;
}

bool isValidPeriod(int start_month, int end_month, int start_day, int end_day)
{
  if (start_month > end_month)
    return false;

  if (start_month == end_month)
    if (start_day > end_day)
      return false;

  return true;
}

int main()
{
  char userids[3][200] = {"user1", "user12", "user3"};
  bool is_valid = true;
  for (int i = 0; i < 3 && is_valid; i++)
  {
    is_valid = isValidID(userids[i]);
    if (!is_valid)
    {
      cout << userids[i] << " is invalid.\n";
    }
  }
}