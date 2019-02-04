#include <iostream>

using std::cout;

struct actMetaData
{
    int duration;
    float priority;
    char *user_id, *title;
};

int DAYS_IN_MONTHS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// http://blog.slickedit.com/2007/11/c-tips-pointers-and-memory-management/

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
    // will always be the ith index of DAYS_IN_MONTHS

    for (int i = 0; i < 12; i++)
    {
        calendar[i] = new int ***[DAYS_IN_MONTHS[i]];

        for (int j = 0; j < DAYS_IN_MONTHS[i]; j++)
        {
            calendar[i][j] = new int **[24];
            for (int k = 0; k < 24; k++)
                calendar[i][j][k] = new int *[10]();
        }
    }
}

void delCal(int *****&calendar)
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
                delete[] calendar[i][j][k];
            delete[] calendar[i][j];
        }
        delete[] calendar[i];
    }

    delete[] calendar;
    calendar = NULL;
}

void resizeActivity(int *****&calendar, int month, int day, int hour, int size,
                    int expand = 10)
{

    int **ptr = new int *[size + expand];

    for (int k = 0; k < size; k++)
        ptr[k] = calendar[month][day][hour][k];

    delete[] calendar[month][day][hour];
    calendar[month][day][hour] = ptr;
}

int getSize(int **&calendar, int month, int day, int hour, int reserve = 0)
{
    int allocated_hours = reserve;

    for (; calendar[month][day][allocated_hours]; allocated_hours++)
        ;

    return allocated_hours;
}

int main()
{
    // Initialize Calendar to the count of months in a year
    int *****calendar = new int ****[12];
    initCal(calendar);
    resizeActivity(calendar, 2, 2, 2, 10);
    int s = 4;
    int *ptr = &s;
    calendar[2][2][2][43] = ptr;
    cout << *calendar[2][2][2][43];
    delCal(calendar);
}