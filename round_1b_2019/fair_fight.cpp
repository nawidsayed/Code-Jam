#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;


long find_max(long *arr, long L, long R){
	long max = - 1000000000; 
	for(long i = L; i <= R; i++){
		if(arr[i] > max){
			max = arr[i];
		}
	}
	return max;
}

int main(){
	ios_base::sync_with_stdio(false); 
	long T,N,K,m1,m2, diff, sum;


	cin >> T;
	for(long t = 0; t < T; t++){
		cin >> N;
		cin >> K;

		long arr1[N];
		long arr2[N];
		for(long i = 0; i < N; i++){
			cin >> arr1[i];
		}

		for(long i = 0; i < N; i++){
			cin >> arr2[i];
		}

		sum = 0;
		for(long L = 0; L < N; L++){
			for(long R = L; R < N; R++){
				m1 = find_max(arr1,L,R);
				m2 = find_max(arr2,L,R);
				diff = m1 - m2;
				if(diff <= K and diff >= -K){
					sum ++;
				}
			}
		}

		cout << "Case #" << t+1 << ": " << sum << endl;
	}	
}