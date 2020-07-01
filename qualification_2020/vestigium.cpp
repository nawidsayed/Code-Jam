#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); 
	long T,N,trace;
    cin >> T;
	for(long t = 0; t < T; t++){
		cin >> N;
        
        long arr[N][N];
        for(long i = 0; i < N; i++){
            for(long j = 0; j < N; j++){
                cin >> arr[i][j] ;
            }
        }

        trace = 0;
        for(long i = 0; i < N; i++){
            trace += arr[i][i];
        }

        long duplicated = 0;
        for(long i = 0; i < N; i++){
            set<int> elements;
            for(long j = 0; j < N; j++){
                elements.insert(arr[i][j]);
            }
            if(elements.size() != N){
                duplicated += 1;
            } 
        }

        long duplicated2 = 0;
        for(long i = 0; i < N; i++){
            set<int> elements;
            for(long j = 0; j < N; j++){
                elements.insert(arr[j][i]);
            }
            if(elements.size() != N){
                duplicated2 += 1;
            } 
        }

        cout << "Case #" << t+1 << ": " << trace <<" " << duplicated <<" " << duplicated2 << endl;        

	}    
}