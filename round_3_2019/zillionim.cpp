#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// long length = 1000;
// long cons = 100;

long length = 1000000000000L;
long cons = 10000000000L;

int main() {
    // Speeds up input reading.
    ios_base::sync_with_stdio(false); 
    long T, W, p, cur, cur_ind, ind, place, ones, twos, total;
    cin >> T;
    cin >> W;

    for(long t = 0; t < T; t++){
        vector<long> v;
        v.push_back(-cons+1);
        v.push_back(length+1);
        p = 0;

        // Mode 1: reducing gaps to a maximum of 2 cons, opponent turn
        while(p >= 0){
            cin >> p;
            v.push_back(p);
            sort(v.begin(), v.end());

            // Getting gaps
            vector<long> gaps;
            for(int i = 1; i < v.size(); i++){
                gaps.push_back(v[i] - v[i-1] - cons);
            }

            // Printing gaps
            // for(int i = 0; i < gaps.size(); i++){
            //     cout << "gap: " << gaps[i] << endl;
            // }

            // Finding biggest gap
            cur = 0;
            cur_ind = 0;
            for(int i = 0; i < gaps.size(); i++){
                if(gaps[i] > cur){
                    cur = gaps[i];
                    cur_ind = i;
                }
            }
            // Leaving mode 1 if gaps are sufficiently small
            if(cur <= cons * 2){
                break;
            }
            if(cur <= cons * 3){
                place = v[cur_ind] + cons;
            } else {
                place = v[cur_ind] + 3*cons;
            }
            cout << place << endl;
            v.push_back(place);
        }

        if(p == -1){
            return 0;
        }

        // Mode 2: Filling and counting gaps, its our turn
        while(p >= 0){
            sort(v.begin(), v.end());
            // Getting gaps
            vector<long> gaps;
            for(int i = 1; i < v.size(); i++){
                gaps.push_back(v[i] - v[i-1] - cons);
            }

            // Counting one gappers and two gappers
            ones = 0;
            twos = 0;
            for(int i = 0; i < gaps.size(); i++){
                if(gaps[i] >= 2*cons){
                    twos++;
                } else if(gaps[i] >= cons){
                    ones++;
                }
            }


            total = ones + twos;
            if(not (total % 2 )){
                // Finding biggest gap
                cur = 0;
                cur_ind = 0;
                for(int i = 0; i < gaps.size(); i++){
                    if(gaps[i] > cur){
                        cur = gaps[i];
                        cur_ind = i;
                    }
                }
                place = v[cur_ind] + cons;
            } else {
                // Finding any valid gap
                cur = 0;
                cur_ind = 0;
                for(int i = 0; i < gaps.size(); i++){
                    if(gaps[i] >= cons){
                        cur = gaps[i];
                        cur_ind = i;
                        break;
                    }
                }
                if(cur == 2*cons){
                    place = v[cur_ind] + cons + 100000;
                } else {
                    place = v[cur_ind] + cons;
                }
                
            }
            cout << place << endl;
            v.push_back(place);            

            cin >> p;
            v.push_back(p);

        }       
        if(p == -1){
            return 0;
        }
    }
}

