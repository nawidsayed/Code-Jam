#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;


int main() {
    // Speeds up input reading.
    ios_base::sync_with_stdio(false); 
    long T, a, N, n, v;
    long lo, hi;
    lo = 16;
    hi = 21;
    long arr[21];
    cin >> T;
    for(long t = 0; t < T; t++){
        for(long d = 0; d < 82; d++){
            cin >> a; 
            v = (d%(lo-1))+1;
            cout << v << " " << 100 << endl;     
        }
        for(long v = lo; v < hi; v++){
            cin >> a; 
            cout << v << " " << 100 << endl;     
        }
        for(long v = lo; v < hi; v++){
            cin >> a; 
            cout << v << " " << 0 << endl;  
            cin >> N;
            arr[v] = N;
            for(long i = 0; i < N; i++){
                cin >> n;
            }    
        }
        // 84
        long best, cur;
        best = 100; 
        for(long v = lo; v < hi; v++){
            if(arr[v] < best){
                cur = v;
                best = arr[v];
            }
        }

        for(long d = 0; d < 10; d++){
            v = (d%5)+lo;
            if(v != cur){
                cin >> a; 
                cout << v << " " << 100 << endl;     

            }      
        }
    }
}

