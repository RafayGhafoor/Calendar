#include <iostream>
using namespace std;

int DAYS[] = {31, 28, 30, 31, 30, 31, 30}; // DAYS IN JANUNARY to JULY

int main() {
  int startMonth = 1, endMonth = 4, startDay = 15, endDay = 20;

  for (int i = startDay;; i++) {

    if (startMonth <= endMonth)
      cout << startMonth << ", " << i << endl;

    if (i == DAYS[startMonth - 1]) // Discard endMonth days; use endDay for it
    {
      i = 0;
      startMonth++;
    }

    if (startMonth == endMonth)
      if (i == endDay)
        break;
  }

  /*
OUTPUT SHOULD BE LIKE THIS: MONTH, DAY from start to end

FROM
1,15
1,16
1,17
...
1,31
2,1
2,2
2,3
2,4
...
2,20
TILL
*/
}