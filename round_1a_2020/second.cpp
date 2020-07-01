#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

void add_pow2(long k, bool reversed, vector<long> &xwalk,vector<long> &ywalk){
    
    for (long i = 0; i <= k; i++){
        if (not reversed) {
            xwalk.push_back(i);
        } else {
            xwalk.push_back(k-i);
        }
        ywalk.push_back(k);
    }
}

void add_baseline(long k, bool reversed, vector<long> &xwalk,vector<long> &ywalk){
    if (not reversed) {
        xwalk.push_back(0);
    } else {
        xwalk.push_back(k);
    }
    ywalk.push_back(k);
}

void output_walks(vector<long> xwalk,vector<long> ywalk){
    for (long i = 0; i < xwalk.size(); i++){
        cout << ywalk[i]+1 << " " << xwalk[i]+1 << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
	long T,N;

    long size = 100;

    long triangle[size][size];
    for (long i = 0; i < size; i++){
        triangle[i][0] = 1;
        triangle[i][i] = 1;
        for (long j = 1; j<i; j++){
            triangle[i][j] = triangle[i-1][j] + triangle[i-1][j-1];
            // cout << i << j << " " <<  triangle[i][j] << endl;
        }
    }

    cin >> T;
    for (long t = 0; t<T; t++){
        cin >> N;
        vector<long> xwalk;
        vector<long> ywalk;
        if (N < 40) {
            for (long i = 0; i < N; i++){
                xwalk.push_back(0);
                ywalk.push_back(i);
            }
        } else {
            xwalk.push_back(0);
            ywalk.push_back(0);

            long number = (N-31) / 2;
            bool reversed = false;
            long sum = 1;
            long fac = 2;
            for (long pow = 1; pow < 30; pow++){
                if (number % 2 == 1){
                    add_pow2(pow, reversed, xwalk, ywalk);
                    reversed = not reversed;
                    sum += fac;
                } else {
                    add_baseline(pow, reversed, xwalk, ywalk);
                    sum ++;
                }

                number /= 2;
                fac *= 2;
            }

            long remainder = N - sum;
            for (long pow = 30; pow < 30 + remainder; pow++){
                add_baseline(pow, reversed, xwalk, ywalk);
                sum ++;
            }

            // cout << "sum " << remainder << endl;

        }

        // long control = 0;
        // for (long i = 0; i< xwalk.size(); i++){
        //     control += triangle[ywalk[i]] [xwalk[i]];
        // }

        // cout << "control " << control << endl;

        cout << "Case #" << t+1 << ":" << endl;
        output_walks(xwalk, ywalk);
    }
}