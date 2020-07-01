#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

template <typename T>
vector<long> sort_indexes(const vector<T> &v) {
    // initialize original index locations
    vector<long> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    // using std::stable_sort instead of std::sort
    // to avoid unnecessary index re-orderings
    // when v contains elements of equal values
    stable_sort(idx.begin(), idx.end(), [&v](long i1, long i2){return v[i1] < v[i2];});

    return idx;  
}


int main() {
	ios_base::sync_with_stdio(false); 
	long T,N,s,e;
    cin >> T;
    long j,c;
	for(long t = 0; t < T; t++){
		cin >> N;
        vector<long> starts, ends, indices;
        for (long i = 0; i < N; i++){
            cin >> s;
            cin >> e;
            starts.push_back(s); 
            ends.push_back(e); 
        } 
    
        indices = sort_indexes(starts);

        long j = -1;
        long c = -1;
        
        char arr[N];
        bool possible = true;

        for (long i: indices){
            cout << i;
            s = starts[i];
            e = ends[i];
            if (s >= c){
                c = e;
                arr[i] = 'C';
            } else if (s >= j){
                j = e;
                arr[i] = 'J';
            } else {
                possible = false;
                break;
            }
        }

        string out;
        if (not possible) {out = "IMPOSSIBLE";}
        else {
            string s(arr);
            out = s;
            }
        cout << "Case #" << t+1 << ": " << out << endl;  
	}    
}