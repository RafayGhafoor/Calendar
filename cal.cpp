#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

using std::cout;

struct activity
{
  int month, day, start_time, end_time;
  float priority;
  char *user_id, *title;
};

void lstAct(char *userID, char *start_time, char *end_time);
void lstImpAct(char userID, char *start_time, char *end_time);
void lstFreePeriod(char *start_time, char *end_time, int days);
void lstClashes(char *start_time, char *end_time, char userID1, char userID2);
void lstFreeSlots(char *start_time, char *end_time, char userID);
void getActStats();
void getCalStats();
void delUser(char userID);
void showCal(char *month);

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
  activity **ptr = new activity *[size + 1];
  std::copy(calendar, calendar + size, ptr);
  delete[] calendar;
  calendar = ptr;
}

void fillCal(activity *****&cal, std::ifstream &fin)
{

  // https://stackoverflow.com/questions/40303500/c-how-to-read-a-line-with-delimiter-until-the-end-of-each-line

  // https://stackoverflow.com/questions/5578631/how-do-you-stop-reading-integer-from-text-file-when-encounter-negative-integer/5578649#5578649
  // Just plain wrong. (Anytime you see istream::eof() as a loop condition, the
  // code is almost certainly wrong.)
  int index, counter = 0;
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
    a.month--, a.day--, a.start_time--, a.end_time--;

    // Calendar Filling from here!

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

    // cout << getActs(cal[a.month][a.day][a.start_time]) << std::endl;

    resizeActs(cal[a.month][a.day][a.start_time]); // Resize the activity box by 1
                                                   // making room for a new activity

    cout << getActs(cal[a.month][a.day][a.start_time]);
  }
}

// void outputCal(activity *****&calendar)
// {
//   cout << "Count of Activities is: " << getActs(calendar[7][5][3]);
// for (int i = 0; i < 12; i++)
// for (int j = 0; j < DAYS_IN_MONTHS[i]; j++)
//   for (int k = 0; k < 24; k++)
//     for (int l = 0; l < getActs(calendar[i][j][k]); l++)
//     {
//       cout << "Count of Activities is: " <<
//       getActs(calendar[i][j][k])
//            << std::endl;
//       cout << "Month is " << i << ", Day is: " << j << ", Hour is: " << k
//            << std::endl
//            << std::endl;
//     }
// }

// void saveCal(activity *****&calendar)
// {
//   cout << calendar[11][20][1][0]->title << std::endl;

// std::ofstream fout("mod_cal.txt");
// cout << calendar[][];
// for (int mon = 0; mon < 12; mon++)
//   for (int day = 0; day < DAYS_IN_MONTHS[mon]; day++)
//     for (int hr = 0; hr < 24; hr++)
//       for (int act = 0; calendar[mon][day][hr] &&
//                         act < getActs(calendar[mon][day][hr]);
//            act++)
//       {
//         cout << calendar[mon][day][hr][act]->title << std::endl;
//         if (calendar[mon][day][hr] && calendar[mon][day][hr][act])
//         {
//           fout << day + 1 << "/";
//           fout << mon + 1 << ",";
//           fout << calendar[mon][day][hr][act][0].start_time + 1 << ",";
//           fout << calendar[mon][day][hr][act][0].end_time + 1 << ",";
//           fout << calendar[mon][day][hr][act]->user_id << ",";
//           fout << calendar[mon][day][hr][act]->title << ",";
//           fout << calendar[mon][day][hr][act]->priority << std::endl;
//         }
//       }
// fout.close();
// }

// void list_activity(activity *****&calendar, int stMonth, int stDate,
//                    int endDate)
// {
//   for (int i = 0; i < 24; i++)
//   {
//     for (int j = 0; calendar[stMonth][stDate][i][j]; j++)
//     {
//       cout << "User Id: " << calendar[stMonth][stDate][i][j][0].user_id <<
//       endl; cout << "Activity Name: " <<
//       calendar[stMonth][stDate][i][j].title
//            << endl;
//       cout << "Avtivity
//           Priority : " << calendar[stMonth][stDate][i][j].priority
//            << endl;
//       cout << "Start Time of activity: " <<
//       calendar[stMonth][stDate][i][j].day
//            << "/" << calendar[stMonth][stDate][i][j].month << endl;
//       cout << "Activity Period: " << calendar[stMonth][stDate][i][j].period
//            << endl;
//     }
//   }
// }

// void displayMenu()
// {
//   char s;

//   while (std::cin >> s)
//   {
//     if (s == '1')
//       listAct();

//     else if (s == '2')
//       listimpAct();

//     else if (s == '3')
//       listFreePeriod();

//     else if (s == '4')
//       listClashAct();

//     else if (s == '5')
//       listFreeSlots();

//     else if (s == '6')
//       getActStats();

//     else if (s == '7')
//       getCalStats();

//     else if (s == '8')
//       delUser();

//     else if (s == '9')
//       saveCal();

//     else if (s == '0')
//       showCal();
//   }
// }

int main()
{
  // Initialize Calendar to the count of months in a year
  std::ifstream fin("test.txt");
  activity *****calendar = new activity ****[12];
  initCal(calendar);
  fillCal(calendar, fin);
  // outputCal(calendar);
  // saveCal(calendar);
  delCal(calendar);
}