#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false); 
	long T,n,a,b,fac,res;
	cin >> T;
	for(long t = 0; t < T; t++){
		cin >> n;
		a = 0;
		b = 0;
		fac = 1;
		while(n>0){
			res = n%10; 
			if(res == 4){
				a += fac*3;
				b += fac*1;
			}
			else{
				a += fac*res;
			}
			fac *=10;
			n /= 10;
		}
		cout << "Case #" << t+1 << ": " << a << " " << b << endl;
	}	
}