#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false); 
	long T,P,Q,x,y;
	char c;
	cin >> T;
	for(long t = 0; t < T; t++){
		cin >> P;
		cin >> Q;
		Q++;
		int xspace[Q];
		int yspace[Q];
		for(long i = 0; i < Q; i++){
			xspace[i] = 0;
			yspace[i] = 0;
		}
		for(long i = 0; i < P; i++){
			cin >> x;
			cin >> y;
			cin >> c;
			if(c == 'N'){
				for(long j = y+1; j < Q; j++){
					yspace[j] ++;
				}
			}
			if(c == 'S'){
				for(long j = 0; j < y; j++){
					yspace[j] ++;
				}
			}
			if(c == 'E'){
				for(long j = x+1; j < Q; j++){
					xspace[j] ++;
				}
			}
			if(c == 'W'){
				for(long j = 0; j < x; j++){
					xspace[j] ++;
				}
			}
		}
		int xmax = -1;
		int ymax = -1;
		int xbest = 0;
		int ybest = 0;
		int xcur, ycur;
		for(long i = 0; i < Q; i++){
			xcur = xspace[i];
			ycur = yspace[i];
			if(xcur > xmax){
				xbest = i;
				xmax = xcur;
			}
			if(ycur > ymax){
				ybest = i;
				ymax = ycur;
			}
		}
		cout << "Case #" << t+1 << ": " << xbest << " " << ybest << endl;
	}	
}