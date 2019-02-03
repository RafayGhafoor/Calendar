#include <iostream>

using std::cout;

struct duration
{
    int month;
    int date;
    int time;
};

struct activity
{
    char *title;
    char *userid;
    duration time;
    float priority;
};

void initCal(int *****&calendar)
{
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
    // will always be the ith index of days_in_months
    int days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int i = 0; i < 12; i++)
    {
        calendar[i] = new int ***[days_in_months[i]];

        for (int j = 0; j < days_in_months[i]; j++)
        {
            calendar[i][j] = new int **[24];
            for (int k = 0; k < 24; k++)
                calendar[i][j][k] = new int *[10];
        }
    }
}

void delCal(int *****&calendar)
{
    // A garbage cleaner function for the memory allocated by the calendar.
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < days_in_months[i]; j++)
        {
            for (int k = 0; k < 24; k++)
                delete[] calendar[i][j][k];
            delete[] calendar[i][j];
        }
        delete[] calendar[i];
    }

    delete[] calendar;
}

int main()
{
    // Initialize Calendar to the count of months in a year
    int *****calendar = new int ****[12];
}