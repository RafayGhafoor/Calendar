#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct activity
{
  int month, day, start_time, end_time;
  float priority;
  char *user_id, *title;
};

void displayAct(activity *&info, int &act_count)
{
  cout << "-------------------------------------------------" << endl;
  if (info->user_id && info->title)
  {
    cout << "UserID: " << info->user_id << endl;
    cout << "Activity Number [" << act_count++ + 1 << ']' << endl;

    cout << "Month: " << info->month + 1 << " | Day: " << info->day + 1
         << " | (" << info->start_time << " - " << info->end_time << ')'
         << endl;

    cout << "Name: " << info->title << endl;

    cout << "Priority: " << info->priority << endl
         << endl;
  }
}

activity *****calendar = new activity ****[12];
// http://thedeepbluecpp.blogspot.com/2014/01/rule-2-make-all-type-conversions.html

// Type conversions should be isolated in their own line, which should consist
// only of the assignment of the result of the type conversion to a variable of
// the target type.

// https://stackoverflow.com/questions/14067153/are-uintptr-t-and-size-t-same?noredirect=1&lq=1

// http://web.archive.org/web/20140828142605/http://www.codeproject.com/Articles/60082/About-size_t-and-ptrdiff_t

const int DAYS_IN_MONTHS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// http://blog.slickedit.com/2007/11/c-tips-pointers-and-memory-management/

// ****************UTILITY FUNCTIONS {BEGIN}**************************

bool isValidID(char userID[])
{
  /*
    Sanity check for userid.

    Following are the rules that can be generalized from the observed dataset:

    i)  UserID always starts with the string "user"
    ii) UserID will never exceed 6 characters "userDD", where D represents a
   digit iii) Digits must come after the string "user"

  */
  bool idStatus = true;
  char begin[] = "user"; // userID must begin with 'user'

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

bool isValidMonth(int month)
{
  // Sanity check for months validity (check is based upon index which will
  // always be 1 less than the month)
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

// *************Function overloading, supporting double (for priority) and int
// array types**************
int findMax(int arr[], const size_t &size)
{
  // Returns maximum number index in the array of integers
  int max_index = 0;
  for (size_t i = 0; i < size; i++)
  {
    if (arr[max_index] <= arr[i])
      max_index = i;
  }

  return max_index;
}

void findMax(float arr[], int out_index[], const size_t &size)
{
  // Returns maximum number index in the array of doubles
  for (size_t i = 0; i < size; i++)
  {
    int max_index = 0;
    for (size_t j = i + 1; j < size; j++)
      if (arr[max_index] <= arr[j])
        max_index = j;
    out_index[i] = max_index;
    arr[max_index] = 0;
  }
}

// *************** UTILITY FUNCTIONS {END}**********************

void initCal(activity *****&calendar)
{
  /* Initializes the calendar having the following format:
Months as a base for pointers containing quad-pointers; pointing towards
> Days > Hours > Activities > Activities Container.
The activities pointer is initially set to 10 i.e., should be able to point
towards 10 activities, in the beginning.

Constants Representation (in loops:
12 - Number of Months
24 - Number of Hours
10 - Number of Pointers for activities, initially
*/

  // Days in months of 2019, used subsequently for the allocation of days
  // pointers and their deallocation; helps keeping track of the days in months
  // and wherever (time in hours > activities > activities container) they point
  // will always be the ith index of DAYS_IN_MONTHS

  for (int i = 0; i < 12; i++)
  {
    calendar[i] = new activity ***[DAYS_IN_MONTHS[i]];

    for (int j = 0; j < DAYS_IN_MONTHS[i]; j++)
    {
      calendar[i][j] = new activity **[24];

      for (int k = 0; k < 24; k++)
        calendar[i][j][k] = new activity *[1]();
    }
  }
}

int getActs(activity **&calendar)
{
  // Returns count of the allocated pointers;   used for checking activities
  // existence.
  // Usage Example: getActs(calendar[0][0][0])

  int act_count = 0;

  while (calendar[act_count])
    act_count++;

  return act_count;
}

void delCal(activity *****&calendar)
{
  // A garbage cleaner function for the memory allocated by the calendar.

  // | The grantation of rights comes with a responsibility to bear. Treat
  // pointers with the respect you would treat a firearm — and you may not find
  // yourself shot in your own foot.| #1

  for (int i = 0; i < 12; i++)
  {
    for (int j = 0; j < DAYS_IN_MONTHS[i]; j++)
    {
      for (int k = 0; k < 24; k++)
      {
        for (int l = 0; calendar[i][j][k] && l < getActs(calendar[i][j][k]);
             l++)
        {
          delete[] calendar[i][j][k][l]->user_id;
          delete[] calendar[i][j][k][l]->title;
          calendar[i][j][k][l] = nullptr;
        }

        if (calendar[i][j])
        {
          delete[] calendar[i][j][k];
          calendar[i][j][k] = nullptr;
        }
      }
      delete[] calendar[i][j];
      calendar[i][j] = nullptr;
    }
    delete[] calendar[i];
    calendar[i] = nullptr;
  }

  delete[] calendar;
  // https://stackoverflow.com/questions/20509734/null-vs-nullptr-why-was-it-replaced
  calendar = nullptr;
}

void resizeActs(activity **&calendar)
{
  // Resizes the pointers of the activity
  const int size = getActs(calendar);
  activity **ptr = new activity *[size + 2];
  // Parameters Source, Source + Size, Destination
  std::copy(calendar, calendar + size, ptr);
  delete[] calendar;
  calendar = nullptr;
  calendar = ptr;
}

void fillCal(activity *****&cal, std::ifstream &fin)
{

  // https://stackoverflow.com/questions/40303500/c-how-to-read-a-line-with-delimiter-until-the-end-of-each-line

  // https://stackoverflow.com/questions/5578631/how-do-you-stop-reading-integer-from-text-file-when-encounter-negative-integer/5578649#5578649
  // Just plain wrong. (Anytime you see istream::eof() as a loop condition, the
  // code is almost certainly wrong.)
  int index = 0;
  char text[200];

  while (fin.getline(text, 200, '/'))
  {
    activity a;
    a.day = atoi(text);
    fin.getline(text, 200, ',');
    a.month = atoi(text);

    // Period is calculated by subtracting (end time - start time),
    // where start time is always smaller than end time

    fin.getline(text, 200, ',');
    a.start_time = atoi(text);
    fin.getline(text, 200, ',');
    a.end_time = atoi(text);

    fin.getline(text, 200, ',');
    a.user_id = new char[strlen(text) + 1];
    strcpy(a.user_id, text);

    fin.getline(text, 200, ','); // Skips actID

    fin.getline(text, 200, ',');
    a.title = new char[strlen(text) + 1];
    strcpy(a.title, text);

    fin.getline(text, 200, '\n');

    a.priority = atof(text);
    a.month--, a.day--;

    // Calendar Filling from here!

    // making room for a new activity
    resizeActs(
        cal[a.month][a.day][a.start_time]); // Resize the activity box by 1

    // Obtain the size and index of unfilled activities
    index = getActs(cal[a.month][a.day][a.start_time]);
    cal[a.month][a.day][a.start_time][index] = new activity;

    activity *myCal = cal[a.month][a.day][a.start_time][index];
    // Put title into calendar
    myCal->month = a.month;
    myCal->day = a.day;
    myCal->title = new char[strlen(a.title) + 1];
    strcpy(myCal->title, a.title);
    myCal->user_id = new char[strlen(a.user_id) + 1];
    strcpy(myCal->user_id, a.user_id);
    myCal->start_time = a.start_time;
    myCal->end_time = a.end_time;
    myCal->priority = a.priority;
  }
}

void outputCal(activity *****&calendar)
{
  int act_count = 0;
  for (int mon = 0; mon < 12; mon++)
    for (int day = 0; day < DAYS_IN_MONTHS[mon]; day++)
      for (int hr = 0; hr < 24; hr++)
        for (int act = 0;
             calendar[mon][day][hr] && act < getActs(calendar[mon][day][hr]);
             act++)
          if (calendar[mon][day][hr] && calendar[mon][day][hr][act])
            displayAct(calendar[mon][day][hr][act], act_count);
}

std::string saveCal(activity *****&calendar,
                    std::string filename = "modified_cal.txt")
{

  std::ofstream fout(filename);
  int act_count = 0;
  for (int mon = 0; mon < 12; mon++)
    for (int day = 0; day < DAYS_IN_MONTHS[mon]; day++)
      for (int hr = 0; hr < 24; hr++)
        for (int act = 0;
             calendar[mon][day][hr] && act < getActs(calendar[mon][day][hr]);
             act++)

          if (calendar[mon][day][hr][act])
          {
            activity *cal = calendar[mon][day][hr][act];
            fout << day + 1 << "/";
            fout << mon + 1 << ",";
            fout << cal->start_time << ",";
            fout << cal->end_time << ",";
            fout << cal->user_id << ",";
            fout << "act" << act_count++ << ",";
            fout << cal->title << ",";
            fout << cal->priority << endl;
          }
  fout.close();
  return filename;
}

void lstAct(char userID[], int st_mon = 0, int end_mon = 11, int start_day = 0,
            int end_day = 30)
{
  cout << "Displaying information for [" << userID << ']' << endl;
  int act_count = 0;

  for (int mon = st_mon; mon <= end_mon; mon++)
  {
    int day_threshold = DAYS_IN_MONTHS[mon];
    if (mon == end_mon)
      day_threshold = end_day;

    for (int day = start_day; day < day_threshold; day++)
      for (int hr = 0; hr < 24; hr++)
        for (int act = 0;
             calendar[mon][day][hr] && act < getActs(calendar[mon][day][hr]);
             act++)
          if (!strcmp(userID, calendar[mon][day][hr][act]->user_id))
            displayAct(calendar[mon][day][hr][act], act_count);
  }
}

void lstImpAct(char userID[], int st_mon = 0, int end_mon = 11,
               int start_day = 0, int end_day = 30)
{
  cout << "Displaying 5 Important Activities for [" << userID << ']' << endl;
  activity *info[100];
  int act_count = 0, info_c;

  for (int mon = st_mon; mon <= end_mon; mon++)
  {
    int day_threshold = DAYS_IN_MONTHS[mon];
    if (mon == end_mon)
      day_threshold = end_day;

    for (int day = start_day; day < day_threshold; day++)
      for (int hr = 0; hr < 24; hr++)
        for (int act = 0;
             calendar[mon][day][hr] && act < getActs(calendar[mon][day][hr]);
             act++)

          if (!strcmp(userID, calendar[mon][day][hr][act]->user_id))
            info[info_c++] = calendar[mon][day][hr][act];
  }

  for (int i = 0; i < info_c; i++)
  {
    int max_ind = 0;

    for (int j = i; j < info_c; j++)
      if (info[max_ind]->priority <= info[j]->priority)
        max_ind = j;
    std::swap(info[max_ind], info[i]);
  }

  for (int i = 0, t = 1; t <= 5; i++)
  {
    if (info[i]->priority > 0)
      displayAct(info[i], t);
  }
}

void lstFreePeriod(int st_time, int end_time, int days)
{
  cout << "To be implemented!" << endl;
}
void lstClashes(int st_time, int end_time, char userID1, char userID2)
{
  cout << "To be implemented!" << endl;
}
void lstFreeSlots(int st_time, int end_time, char userID)
{
  cout << "To be implemented!" << endl;
}
void getActStats() { cout << "To be implemented!" << endl; }
void getCalStats() { cout << "To be implemented!" << endl; }
void delUser(char userID) { cout << "To be implemented!" << endl; }
void dispMonth(int month) { cout << "To be implemented!" << endl; }

void dispFeatures()
{
  cout << "Following features are supported by calendar. make a "
          "choice.\n\n";

  cout << "00 - List all the activities of a user during a time period.\n01 "
          "- "
          "List the 5 most important activities of a given user during "
          "time.\n02 - Longest free period time.\n03 - Clashing activities "
          "of "
          "a pair of users during a time period.\n04 - List all hour slots "
          "of "
          "a user that are free.\n05 - Display activity stats of a given "
          "month.\n06 - Calendar Stats for a whole year.\n07 - Remove a "
          "user "
          "from calendar.\n08 - Save the calendar.\n09 - Display month of a "
          "calendar.\n'S' - Show Features Menu.\n'Q' - Exit program.\n";
}

char *getID()
{
  static char ID[200];
  cout << "Enter the user ID (eg: user49): ";
  while (cin >> ID)
  {
    if (isValidID(ID))
      break;
    cout << "Invalid ID specified." << endl;
  }
  return ID;
}

int getMonth()
{
  int mon;
  cout << "Enter month number (1-12): ";
  while (cin >> mon)
  {
    if (isValidMonth(--mon))
      return mon;
    cout << "Invalid Month specified." << endl;
  }
  return mon;
}

int getDay()
{
  int day;
  cout << "Enter day number (1-31): ";
  while (cin >> day)
  {
    if (isValidDay(--day))
      return day;
    cout << "Invalid Day specified." << endl;
  }
  return day;
}

void getPeriod(int info[], int size)
{
  cout << "Enter info according to Start Month, End Month, Start Day and "
          "End "
          "Day.\n\n";
  while (1)
  {
    int m_s = getMonth(), m_e = getMonth(), d_s = getDay(), d_e = getDay();
    if (isValidPeriod(--m_s, --m_e, --d_s, --d_e))
    {
      info[0] = m_s;
      info[1] = m_e, info[2] = d_s, info[3] = d_e;
      break;
    }
  }
}

void displayMenu()
{
  cout << R"(
########################################################
########################################################
########################################################
#              _______________________                 #
#                W E L C O M E  T O                    #
#         >       |C A L E N D A R|         <          #
#              -----------------------                 #
########################################################
########################################################
########################################################
########################################################
########################################################
########################################################
)" << endl
       << endl;

  dispFeatures();
  cout << endl
       << endl;
  cout << ">>> ";
  std::string inp;

  char s;

  while (cin >> inp)
  {
    if (inp.length() != 1)
    {
      cout << "Expected single character\n>>> ";
      continue;
    }

    s = inp[0];

    if (s == '0')
    {
      char *user;
      user = getID();
      int m = getMonth(), m1 = getMonth(), d = getDay(), d1 = getDay();
      lstAct(user, m, m1, d, d1);
    }

    else if (s == '1')
    {
      char *user;
      user = getID();
      int m = getMonth(), m1 = getMonth(), d = getDay(), d1 = getDay();
      lstImpAct(user, m, m1, d, d1);
    }

    else if (s == '2')
      cout << "To be implemented!" << endl;
    // lstFreePeriod();

    else if (s == '3')
      cout << "To be implemented!" << endl;
    // lstClashes();

    else if (s == '4')
      cout << "To be implemented!" << endl;
    // lstFreeSlots();

    else if (s == '5')
      cout << "To be implemented!" << endl;
    // getActStats();

    else if (s == '6')
      cout << "To be implemented!" << endl;
    // getCalStats();

    else if (s == '7')
      cout << "To be implemented!" << endl;
    // delUser();

    else if (s == '8')
    {
      cout << "Calendar has been saved in <" << saveCal(calendar) << ">\n";
    }

    else if (s == '9')
      cout << "To be implemented!" << endl;
    // dispMonth();

    else if (toupper(s) == 'S')
      dispFeatures();

    else if (toupper(s) == 'Q')
    {
      cout << "\n**** Good Bye! ****\n"
           << endl;
      break;
    }

    else
      cout << "Invalid option Entered. try again\n";
    cout << ">>> ";
  }
}

int main()
{
  // Initialize Calendar to the count of months in a year
  std::ifstream fin("calendar1.dat");
  initCal(calendar);
  fillCal(calendar, fin);
  // outputCal(calendar);
  displayMenu();
  delCal(calendar);
}