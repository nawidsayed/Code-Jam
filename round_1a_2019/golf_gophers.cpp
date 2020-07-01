#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); 
	long T,M,N,a,r;
    cin >> T;
    cin >> N;
    cin >> M;

	for(long t = 0; t < T; t++){
        vector<long> divisors = {17,16,13,11,9,5,7};
        vector<long> residuals;
        for (long divisor: divisors) {
            for (long mill = 0; mill < 18; mill++){
                cout << divisor << " ";
            }
            cout << endl;

            r = 0;
            for (long mill = 0; mill < 18; mill++){
                cin >> a;
                r += a;
            }

            r = r % divisor;        
            residuals.push_back(r);
        }
        long out = 0;
        long d,r;
        while (true) {
            out++;
            bool correct = true;
            for (long i = 0; i < divisors.size();    i++){
                d = divisors[i];
                r = residuals[i];
                if (out % d != r){
                    correct = false;
                    break;
                }
            }
            if (correct) break;
        }

        cout << out << endl;
        cin >> a;
        if (a == -1) {
            return 0;
        }


    }
}