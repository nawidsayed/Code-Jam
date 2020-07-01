#include <iostream>
#include <cmath>
#include <string>
using namespace std;


int main() {
    long t, d, n;
    cin >> t;
    for(long i = 0; i < t; i++){
        cin >> d;
        cin >> n;
        long s,k;
        double latest = 0;
        double time;
        for(long j=0; j<n; j++){
            cin >> k;
            cin >> s;
            time = double((d-k)) / s;
            if(time > latest){
                latest = time;
            }
        }
        double x = double(d)/latest;
        cout.precision(10);
        cout << "Case #" << i+1 << ": " << x << endl;
    }
    

}

