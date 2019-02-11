#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

struct activity {
  char *title;
  char *userid;
  int duration;
  float priority;
};

bool ValidMonth(int month) {
  if (month >= 1 && month <= 12)
    return true;
  return false;
}

// void SetColor(int value) {
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
// }

void allocateCalendar(activity *****&calendar, int days[]) {
  calendar = new activity ****[12]; // Months array.

  for (int i = 0; i < 12; i++) {
    calendar[i] = new activity ***[days[i]]; // For days.
    for (int j = 0; j < days[i]; j++) {
      calendar[i][j] = new activity **[24]; // For Hours.
    }
  }
}

void InitializeActivity(activity *****&calendar, int days[]) {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < days[i]; j++) {
      for (int k = 0; k < 24; k++)
        calendar[i][j][k] = nullptr;
    }
  }
}

void Resize(activity **&calendar, int &size) {
  if (size == 0)
    size++;

  activity **temp = new activity *[size + 1];
  for (int i = 0; i < size; i++)
    temp[i] = calendar[i];
  delete[] calendar;
  temp[size] = nullptr;
  calendar = temp;
  size++;
}

void EnterData(activity *****&calendar, int activitySize[12][31][24]) {
  ifstream fin("calendar1.dat");
  int countLine = 1, month, day, startHour, endHour, ignore = 0, storeActivity,
      size = 0, time = 0;
  char *temp = new char[250];
  temp[0] = {0};
  if (fin.is_open()) {
    while (fin >> day) {
      fin.ignore();
      fin >> month;
      fin.ignore();
      fin >> startHour;
      fin.ignore();
      fin >> endHour;
      fin.ignore();
      time = endHour - startHour;
      storeActivity = 0;
      if (activitySize[month - 1][day - 1][startHour] == 0) {
        calendar[month - 1][day - 1][startHour] = new activity *[1];
        calendar[month - 1][day - 1][startHour][storeActivity] = nullptr;
        calendar[month - 1][day - 1][startHour][storeActivity] = new activity;
        Resize(calendar[month - 1][day - 1][startHour],
               activitySize[month - 1][day - 1][startHour]);
      } else {
        size = activitySize[month - 1][day - 1][startHour];
        for (; storeActivity < size; storeActivity++) {
          if (calendar[month - 1][day - 1][startHour][storeActivity] ==
              nullptr) {
            calendar[month - 1][day - 1][startHour][storeActivity] =
                new activity;
            Resize(calendar[month - 1][day - 1][startHour],
                   activitySize[month - 1][day - 1][startHour]);
            break;
          }
        }
      }
      calendar[month - 1][day - 1][startHour][storeActivity]->duration = time;
      fin.getline(temp, 250, ',');
      calendar[month - 1][day - 1][startHour][storeActivity]->userid =
          new char[strlen(temp) + 1];
      strcpy(calendar[month - 1][day - 1][startHour][storeActivity]->userid,
             temp);
      temp[0] = {0};
      for (int i = countLine; i > 0;) {
        i = i / 10;
        ignore++;
      }
      fin.ignore(4 + ignore);
      fin.getline(temp, 250, ',');
      calendar[month - 1][day - 1][startHour][storeActivity]->title =
          new char[strlen(temp) + 1];
      strcpy(calendar[month - 1][day - 1][startHour][storeActivity]->title,
             temp);
      fin >> calendar[month - 1][day - 1][startHour][storeActivity]->priority;
      temp[0] = {0};
      ignore = 0;
      countLine++;
    }
    fin.close();
  } else
    cout << "Unable to open file.";
}

void SaveCalendar(activity *****&calendar, int activitySize[12][31][24],
                  int days[]) {
  ofstream fout("calendar2.txt");
  int countLine = 0;
  if (fout.is_open()) {
    for (int i = 0; i < 12; i++) {

      for (int j = 0; j < days[i]; j++) {

        for (int k = 0; k < 24; k++) {

          for (int l = 0; l < activitySize[i][j][k] - 1; l++) {
            if (calendar[i][j][k][l] != nullptr) {
              fout << j + 1 << "/";
              fout << i + 1 << ",";
              fout << k << ",";
              fout << calendar[i][j][k][l]->duration + k << ",";
              fout << "act" << countLine << ",";
              fout << calendar[i][j][k][l]->userid << ",";
              fout << calendar[i][j][k][l]->title << ",";
              fout << calendar[i][j][k][l]->priority << endl;
              countLine++;
            }
          }
        }
      }
    }
    fout.close();
    cout << "Data saved successfully!/n";
  } else
    cout << "Unable to open file.";
}

void ListActivites(activity *****&calendar, int activitySize[12][31][24],
                   int days[]) {}

void MonthName(int month) {
  if (month == 1)
    cout << "\t---Jan---\n";
  else if (month == 2)
    cout << "\t---Feb---\n";
  else if (month == 3)
    cout << "\t---Mar---\n";
  else if (month == 4)
    cout << "\t---Apr---\n";
  else if (month == 5)
    cout << "\t---May---\n";
  else if (month == 6)
    cout << "\t---Jun---\n";
  else if (month == 7)
    cout << "\t---Jul---\n";
  else if (month == 8)
    cout << "\t---Aug---\n";
  else if (month == 9)
    cout << "\t---Sep---\n";
  else if (month == 10)
    cout << "\t---Oct---\n";
  else if (month == 11)
    cout << "\t---Nov---\n";
  else if (month == 12)
    cout << "\t---Dec---\n";
}

void PrintMonth(int activitySize[12][31][24], int days[], int month) {
  if (ValidMonth(month) == true) {
    int size = 0, nullCount = 0;
    // char temp[20];
    bool flag = false;
    // SetColor(15);
    MonthName(month);
    cout << "  Su"
         << " Mo"
         << " Tu"
         << " We"
         << " Th"
         << " Fr"
         << " Sa\n";
    cout << " ";
    for (int i = 0, j = 4; i < days[month - 1]; i++) {
      nullCount = 0;
      flag = false;
      for (int k = 0; k < 24; k++)
        if (activitySize[month - 1][i][k] == 0)
          nullCount++;
      if (nullCount == 24)
        flag = true;
      if (i % 7 == 0 && i != 0) {
        cout << endl << " ";
        j++;
      }
      if (i <= 7 && flag == false)
        cout << " " << i + 1 << " ";
      else if (i > 7 && i < 9 && flag == false)
        cout << " " << i + 1;
      else if (i == 9 && flag == false)
        cout << " " << i + 1 << " ";
      else if (i > 9 && flag == false)
        cout << " " << i + 1;
      if (i <= 7 && nullCount == 24 && flag == true) {
        // SetColor(14);
        cout << " " << i + 1 << " ";
        // SetColor(15);
        flag = false;
      } else if (i > 7 && i < 9 && nullCount == 24 && flag == true) {
        // SetColor(14);
        cout << " " << i + 1;
        // SetColor(15);
        flag = false;
      } else if (i == 9 && nullCount == 24 && flag == true) {
        // SetColor(14);
        cout << " " << i + 1 << " ";
        // SetColor(15);
        flag = false;
      } else if (i > 9 && nullCount == 24 && flag == true) {
        // SetColor(14);
        cout << " " << i + 1;
        // SetColor(15);
        flag = false;
      }
    }
  } else
    cout << "Invalid Month!";
}

void DeleteUser(activity *****&calendar, int activitySize[12][31][24],
                int days[], char search[]) {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < days[i]; j++) {
      for (int k = 0; k < 24; k++) {
        for (int l = 0; l < activitySize[i][j][k] - 1; l++) {
          if (strcmp(calendar[i][j][k][l]->userid, search) == 0) {
            delete[] calendar[i][j][k][l]->userid;
            delete[] calendar[i][j][k][l]->title;
            delete[] calendar[i][j][k][l];
            calendar[i][j][k][l] = nullptr;
          }
        }
      }
    }
  }
}

double maxFunction(double data[], int size, float &index) {
  int max = 0;
  for (int i = 0; i < size; i++) {
    if (max < data[i]) {
      max = data[i];
      index = i + 1;
    }
  }
  return max;
}

void MonthStats(activity *****&calendar, int activitySize[12][31][24],
                int days[], int month) {
  if (ValidMonth(month) == true) {
    int sum = 0, priorityCount = 0, maxPriority = 0;
    float prioritySum = 0, AvgPriority = 0, busyday = 0, max = 0;
    double *largest = new double[days[month - 1]];
    for (int i = 0; i < days[month - 1]; i++) {
      for (int j = 0; j < 24; j++) {
        if (activitySize[month - 1][i][j] != 0) {
          sum = sum + activitySize[month - 1][i][j] - 1;
          max = max + activitySize[month - 1][i][j] - 1;
        }
      }
      largest[i] = max;
      max = 0;
    }
    max = maxFunction(largest, days[month - 1], busyday);

    for (int i = 0; i < days[month - 1]; i++) {
      for (int j = 0; j < 24; j++) {
        if (activitySize[month - 1][i][j] != 0) {
          for (int k = 0; k < activitySize[month - 1][j][k] - 1; k++) {
            if (calendar[month - 1][i][j][k] != nullptr) {
              prioritySum =
                  prioritySum + calendar[month - 1][i][j][k]->priority;
              priorityCount++;
            }
          }
        }
      }
      largest[i] = prioritySum / priorityCount;
      priorityCount = prioritySum = 0;
    }
    maxPriority = maxFunction(largest, days[month - 1], AvgPriority);
    cout << "Total Activites = " << sum << endl;
    cout << "Average Activities Per Day = " << sum / days[month - 1] << endl;
    cout << "Busiest Day of Month = " << busyday << endl;
    cout << "Number of Activites in Busiest Day = " << max << endl;
    cout << "Highest Average Priority of Activites = " << maxPriority
         << endl; // Need to fix.
    cout << "Number of Activites in Highest Priority Day = " << AvgPriority
         << endl;
    delete[] largest;
    largest = nullptr;
  } else
    cout << "Invalid Month!";
}

void CalendarStats(int activitySize[12][31][24], int days[]) {
  int sum = 0, max = 0;
  float busymonth = 0;
  double largest[12] = {0};
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < days[i]; j++) {
      for (int k = 0; k < 24; k++) {
        if (activitySize[i][j][k] != 0) {
          max = max + (activitySize[i][j][k] - 1);
          sum = sum + (activitySize[i][j][k] - 1);
        }
      }
    }
    largest[i] = max;
    max = 0;
  }
  max = maxFunction(largest, 12, busymonth);
  cout << "Total Activites = " << sum << endl;
  cout << "Average Activities Per Month = " << sum / 12 << endl;
  cout << "Busiest Month = " << busymonth << endl;
  cout << "Number of Activites in Busiest Month = " << max << endl;
}

void Deallocate(activity *****&calendar, int activitySize[12][31][24],
                int days[]) {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < days[i]; j++) {
      for (int k = 0; k < 24; k++) {
        for (int l = 0; l < activitySize[i][j][k] - 1; l++) {
          delete[] calendar[i][j][k][l]->userid;
          delete[] calendar[i][j][k][l]->title;
          delete[] calendar[i][j][k][l];
          calendar[i][j][k][l] = nullptr;
        }
        delete[] calendar[i][j][k];
      }
      delete[] calendar[i][j];
    }
    delete[] calendar[i];
  }
  delete[] calendar;
  calendar = nullptr;
}

int main() {
  activity *****calendar;
  int activitySize[12][31][24];
  // int month = 0;
  // char tempDel[200] = "user78";
  int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  for (int i = 0; i < 12; i++) // 1 activitiy initially.
    for (int j = 0; j < 31; j++)
      for (int k = 0; k < 24; k++)
        activitySize[i][j][k] = {0};

  allocateCalendar(calendar, days);
  InitializeActivity(calendar, days);
  EnterData(calendar, activitySize);
  /*cout << "Enter Month Number:";
cin >> month;
cout << endl;
PrintMonth(activitySize, days, month);
DeleteUser(calendar, activitySize, days,tempDel);*/
  // SaveCalendar(calendar, activitySize, days);
  MonthStats(calendar, activitySize, days, 5);
  // CalendarStats(activitySize, days);
  Deallocate(calendar, activitySize, days);
}