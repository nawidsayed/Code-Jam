#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// Number guessing in a stupid way

int main() {
  int t, a, b, n;
  cin >> t; // read t. cin knows that t is an int, so it reads it as such.
  for (int i = 1; i <= t; ++i) {
    cin >> a >> b; 
    cin >> n;
    int guess = a+1;
    string s;
    while(true){
    	cout << guess << endl;
    	cin >> s;

    	bool bl = s.compare("CORRECT");
    	if (!bl){
    		break;
    	} 
    	guess++;
    }
    // cout << "Case #" << i << ": " << (n + m) << " " << (n * m) << endl;
    // cout knows that n + m and n * m are ints, and prints them accordingly.
    // It also knows "Case #", ": ", and " " are strings and that endl ends the line.
  }
  return 0;
}

