#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <set>
using namespace std;






int main(){
	ios_base::sync_with_stdio(false); 
	long T,N;

	long c1,j1,c2,j2;
	long cd,jd,s,l,r;

	cin >> T;
	for(long t = 0; t < T; t++){
		cin >> N;
		long carr[N];
		long jarr[N];
		for(long i = 0; i < N; i++){
			cin >> carr[i];
			cin >> jarr[i];
		}
		set<double> fracs;

		for(long i = 1; i < N; i++){
			for(long k = 0; k < i; k++){
				c1 = carr[i];
				c2 = carr[k];
				j1 = jarr[i];
				j2 = jarr[k];

				cd = c2-c1;
				jd = j2-j1;

				if(cd*jd < 0){
					if(-cd/jd == 0){
						s = cd;
						l = jd;
					} else {
						s = jd;
						l = -cd;
					}
					r = 1000000000L*l/s;

					// cout << r << endl;
					fracs.insert(r);
				}
			}
		}

		// cout << fracs.size() << endl;

		cout << "Case #" << t+1 << ": " << fracs.size()+1 << endl;
	}	
}