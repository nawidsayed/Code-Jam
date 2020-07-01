#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

long power(long base, long exp){
    long fac = 1;
    for(long t = 0; t < exp; t++){
        fac *= base;
    }
    return fac;
}

int main() {
    // Speeds up input reading.
    ios_base::sync_with_stdio(false); 
    long T, W, a;
    long r1,r2,r3,r4,r5,r6;
    cin >> T;
    cin >> W;
    for(long t = 0; t < T; t++){
        cout << 200 << endl;
        cin >> a;
        
        r4 = a/power(2,50);
        a -= r4 * power(2,50);
        r5 = a/power(2,40);
        a -= r5 * power(2,40);
        r6 = a/power(2,33);

        // cout << power(2,50); 
        // cout << r4 << r5 << r6 << endl;

        cout << 55 << endl;
        cin >> a;

        a -= r4*power(2,13);
        a -= r5*power(2,11);
        a -= r6*power(2,9);

        r1 = a/power(2,55);
        a -= r1*power(2,55);
        r2 = a/power(2,27);
        a -= r2*power(2,27);
        r3 = a/power(2,18);

        cout << r1 << " ";
        cout << r2 << " ";
        cout << r3 << " ";
        cout << r4 << " ";
        cout << r5 << " ";
        cout << r6 << " ";

        cout << endl;
        cin >> a;
        if(a == -1){
            return 0;
        }
    }
}

