#include <iostream>

using namespace std;

char *getName() {
  static char user[200];
  cout << "Please enter user name: " << endl;
  cin >> user;
  return user;
}
int main() { getName(); }