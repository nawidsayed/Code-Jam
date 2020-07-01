#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

long query(long k){
    cout << k+1 << endl;
    long d;
    cin >> d;
    return d;
}

void reverse(vector<long> &vec){
    reverse(vec.begin(), vec.end());
}

void invert(vector<long> &vec){
    for(long i =0; i<vec.size(); i++){
        vec[i] = 1-vec[i];
    }
}

void switcher(vector<long> &vec, bool same){
    long s = 0;
    long e = vec.size() - 1;
    while (s<e) {
        if ((vec[s] == vec[e]) == same){
            vec[s] = 1-vec[s];
            vec[e] = 1-vec[e];
        }
        s++;
        e--;
    }
}

int main() {
	ios_base::sync_with_stdio(false); 
	long T,B,d;
    string response;
    cin >> T;
    cin >> B;

    vector<long> digits;

    for(long i = 0; i < B; i++){
        digits.push_back(0);
    }
    
	for(long t = 0; t < T; t++){

        long index_same = -1;
        long index_diff = -1;

        long cur_same, cur_diff;
        long next_same, next_diff; 

        long s = 0;
        long e = B-1;

        long queries = 0;

        while (true) {

            if (queries % 10 == 0) {
                if (index_same != -1){
                    next_same = query(index_same);
                    queries ++;
                    if (next_same != cur_same) {
                        switcher(digits, true);
                        cur_same = next_same;
                    }
                } else {
                    query(0);
                    queries ++;
                }
                if (index_diff != -1){
                    next_diff = query(index_diff);
                    queries ++;
                    if (next_diff != cur_diff) {
                        switcher(digits, false);
                        cur_diff = next_diff;
                    }
                } else {
                    query(0);
                    queries ++;
                }
            } else if(e < s) {
                break;
            } else {
                digits[s] = query(s);
                digits[e] = query(e);
                queries += 2;
                if (index_same == -1) {
                    if (digits[s] == digits[e]){
                        index_same = s;
                        cur_same = digits[s];
                    }
                }
                if (index_diff == -1) {
                    if (digits[s] != digits[e]){
                        index_diff = s;
                        cur_diff = digits[s];
                    }
                }
                s++;
                e--;
                
            }
        }

        vector<char> vecc;
        for (long i=0; i<B; i++){
            if (digits[i] == 1){
                vecc.push_back('1');
            } else {
                vecc.push_back('0');
            }
        }

        string out(vecc.begin(), vecc.end());

        cout << out << endl;
        cin >> response;
        if(response =="N"){
            return 0;
        }
	}    
}