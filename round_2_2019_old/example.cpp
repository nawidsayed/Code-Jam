#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;






int main(){
	ios_base::sync_with_stdio(false); 
	long T,N, c,j, cp, jp, ck, jk;
	long c1,j1, c2,j2;
	c1 = 1000000000;
	j1 = 1;
	c2 = 1;
	j2 = 1000000000;

	cin >> T;
	for(long t = 0; t < T; t++){
		cin >> N;
		cp = 0;
		jp = 0;
		for(long i = 0; i < N; i++){
			cin >> c;
			cin >> j;

			ck = c - cp;
			jk = j - jp;

			if (ck <= 0 and jk <= 0){
				cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
				break;
			}

			if(ck >= 0 and jk >= 0 and ck+jk > 0){
				continue;
			}

			if(ck < 0 and ck*c2 + jk*j2 < 0){
				c2 = jk;
				j2 = -ck;
			}

			if(jk < 0 and ck*c1 + jk*j1 < 0){
				c1 = -jk;
				j1 = ck;
			}

			if(c1 * j2 < c2 * j1){
				cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
				break	;
			}
		}

		cout << c1 << " "<< j1 << " " << c2 << " " << j2 << endl;
		// cout << "Case #" << t+1 << ": " << sum << endl;
	}	
}