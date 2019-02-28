#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

struct activity
{
  int month, day, start_time, end_time;
  float priority;
  char *user_id, *title;
};

activity *****calendar = new activity ****[12];
// http://thedeepbluecpp.blogspot.com/2014/01/rule-2-make-all-type-conversions.html

// Type conversions should be isolated in their own line, which should consist
// only of the assignment of the result of the type conversion to a variable of
// the target type.

// https://stackoverflow.com/questions/14067153/are-uintptr-t-and-size-t-same?noredirect=1&lq=1

// http://web.archive.org/web/20140828142605/http://www.codeproject.com/Articles/60082/About-size_t-and-ptrdiff_t

const int DAYS_IN_MONTHS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// http://blog.slickedit.com/2007/11/c-tips-pointers-and-memory-management/

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

int getIndex(activity **&calendar)
{
  int index = 0;

  while (calendar[index])
    index++;

  return index;
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
  const int size = getIndex(calendar);
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

    // Put title into calendar
    cal[a.month][a.day][a.start_time][index]->title =
        new char[strlen(a.title) + 1];

    strcpy(cal[a.month][a.day][a.start_time][index]->title, a.title);

    cal[a.month][a.day][a.start_time][index]->user_id =
        new char[strlen(a.user_id) + 1];

    strcpy(cal[a.month][a.day][a.start_time][index]->user_id, a.user_id);
    cal[a.month][a.day][a.start_time][index]->start_time = a.start_time;

    cal[a.month][a.day][a.start_time][index]->end_time = a.end_time;

    cal[a.month][a.day][a.start_time][index]->priority = a.priority;
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
        {
          cout << "-------------------------------------------------" << endl;
          if (calendar[mon][day][hr] && calendar[mon][day][hr][act])
          {
            cout << "UserID: " << calendar[mon][day][hr][act]->user_id << endl;
            cout << "Activity Number [" << act_count++ + 1 << ']' << endl;

            cout << "Month: " << mon + 1 << " | Day: " << day + 1 << " | ("
                 << calendar[mon][day][hr][act][0].start_time + 1 << " - "
                 << calendar[mon][day][hr][act][0].end_time + 1 << ')' << endl;

            cout << "Name: " << calendar[mon][day][hr][act]->title << endl;

            cout << "Priority: " << calendar[mon][day][hr][act]->priority
                 << endl
                 << endl;
          }
        }
}

void saveCal(activity *****&calendar,
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
        {
          if (calendar[mon][day][hr] && calendar[mon][day][hr][act])
          {
            fout << day + 1 << "/";
            fout << mon + 1 << ",";
            fout << calendar[mon][day][hr][act][0].start_time + 1 << ",";
            fout << calendar[mon][day][hr][act][0].end_time + 1 << ",";
            fout << calendar[mon][day][hr][act]->user_id << ",";
            fout << "act" << act_count++ << ",";
            fout << calendar[mon][day][hr][act]->title << ",";
            fout << calendar[mon][day][hr][act]->priority << endl;
          }
        }
  fout.close();
}

void lstAct(char userID[], int mon = 0, int start_day = 0, int end_day = 30)
{
  cout << "Displaying information for [" << userID << ']' << endl;
  int act_count = 0;
  for (int day = start_day; day < end_day; day++)
    for (int hr = 0; hr < 24; hr++)
      for (int act = 0;
           calendar[mon][day][hr] && act < getActs(calendar[mon][day][hr]);
           act++)
      {
        if (!strcmp(userID, calendar[mon][day][hr][act]->user_id))
        {

          cout << "-------------------------------------------------" << endl;

          cout << "Activity Number [" << act_count++ + 1 << ']' << endl;

          cout << "Month: " << mon + 1 << " | Day: " << day + 1 << " | ("
               << calendar[mon][day][hr][act][0].start_time + 1 << " - "
               << calendar[mon][day][hr][act][0].end_time + 1 << ')' << endl;

          cout << "Name: " << calendar[mon][day][hr][act]->title << endl;

          cout << "Priority: " << calendar[mon][day][hr][act]->priority << endl
               << endl;
        }
      }
}

void lstImpAct(char userID, int st_time, int end_time)
{
  cout << "Hello, World!" << endl;
}
void lstFreePeriod(int st_time, int end_time, int days)
{
  cout << "Hello, World!" << endl;
}
void lstClashes(int st_time, int end_time, char userID1, char userID2)
{
  cout << "Hello, World!" << endl;
}
void lstFreeSlots(int st_time, int end_time, char userID)
{
  cout << "Hello, World!" << endl;
}
void getActStats() { cout << "Hello, World!" << endl; }
void getCalStats() { cout << "Hello, World!" << endl; }
void delUser(char userID) { cout << "Hello, World!" << endl; }
void showCal(char month[]) { cout << "Hello, World!" << endl; }
void dispMonth(int month) { cout << "Hello, World!" << endl; }

void dispFeatures()
{
  cout << "Following features are supported by calendar. Please make a "
          "choice.\n\n";

  cout << "00 - List all the activities of a user during a time period.\n01 - "
          "List the 5 most important activities of a given user during "
          "time.\n02 - Longest free period time.\n03 - Clashing activities of "
          "a pair of users during a time period.\n04 - List all hour slots of "
          "a user that are free.\n05 - Display activity stats of a given "
          "month.\n06 - Calendar Stats for a whole year.\n07 - Remove a user "
          "from calendar.\n08 - Save the calendar.\n09 - Display month of a "
          "calendar.\n'S' - Show Features Menu.\n'Q' - Exit program.\n";
}

char *getID()
{
  char ID[200];
  cout << endl;
  while (1)
  {
    cout << "Please enter the user ID: ";
    cin >> ID;
    if (isValidID(ID))
      return ID;
    else
      cout << "Invalid ID specified." << endl;
  }
  return ID;
}

int getMonth()
{
  char mon;
  cout << endl;
  while (1)
  {
    cout << "Please enter month number: ";
    cin >> mon;
    mon = ctoi(mon);
    if (isValidMonth(mon))
      return mon;
    else
      cout << "Invalid Month specified." << endl;
  }
  return mon;
}

int getDay()
{
  char day;
  cout << endl;
  while (1)
  {
    cout << "Please enter day number: ";
    cin >> day;
    day = ctoi(day);
    if (isValidDay(day))
      return day;
    else
      cout << "Invalid Day specified." << endl;
  }
  return day;
}

int getPeriod(int info[], int size)
{
  cout << "Enter info according to Start Month, End Month, Start Day and End Day.\n\n";
  while (1)
  {
    int m_s = getMonth(), m_e = getMonth(), d_s = getDay(), d_e = getDay();
    if (isValidPeriod(m_s, m_e, d_s, d_e)))
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

  while (std::cin >> inp)
  {
    if (inp.length() != 1)
    {
      cout << "Expected single character\n>>> ";
      continue;
    }

    s = inp[0];
    if (s == '0')
    {
      char user[] = "user49";
      lstAct(user, 0, 16, 20);
    }

    else if (s == '1')
      cout << "test" << endl;
    // lstimpAct();

    else if (s == '2')
      cout << "test" << endl;
    // lstFreePeriod();

    else if (s == '3')
      cout << "test" << endl;
    // lstClashes();

    else if (s == '4')
      cout << "test" << endl;
    // lstFreeSlots();

    else if (s == '5')
      cout << "test" << endl;
    // getActStats();

    else if (s == '6')
      cout << "test" << endl;
    // getCalStats();

    else if (s == '7')
      cout << "test" << endl;
    // delUser();

    else if (s == '8')
      cout << "test" << endl;
    // saveCal();

    else if (s == '9')
      cout << "test" << endl;
    // dispMonth();

    else if (toupper(s) == 'S')
      dispFeatures();

    else if (toupper(s) == 'Q')
    {
      cout << "GoodBye!\n"
           << endl;
      break;
    }

    else
      cout << "Invalid option entered. Please try again\n";
    cout << ">>> ";
  }
}

int main()
{
  // Initialize Calendar to the count of months in a year
  std::ifstream fin("calendar1.dat");
  initCal(calendar);
  fillCal(calendar, fin);
  displayMenu();
  outputCal(calendar);
  delCal(calendar);
}