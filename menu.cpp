#include <cctype>
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

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
      listAct();

    else if (s == '1')
      listimpAct();

    else if (s == '2')
      listFreePeriod();

    else if (s == '3')
      listClashes();

    else if (s == '4')
      listFreeSlots();

    else if (s == '5')
      getActStats();

    else if (s == '6')
      getCalStats();

    else if (s == '7')
      delUser();

    else if (s == '8')
      saveCal();

    else if (s == '9')
      dispMonth();

    else if (toupper(s) == 'S')
      dispFeatures();

    else if (toupper(s) == 'Q')
    {
      cout << "GoodBye!" << endl;
      break;
    }

    else
      cout << "Invalid option entered. Please try again\n";
    cout << ">>> ";
  }
}

int main() { displayMenu(); }
