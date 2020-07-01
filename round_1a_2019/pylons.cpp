#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

int jumps(long x, vector<long> &vecx, vector<long> &vecy, long X, long Y){
    for (long y= 0; y<Y; y++){
        vecx.push_back(x%X);
        vecy.push_back(y);
        x += 2;
    }
    return x;
}

int main() {
	ios_base::sync_with_stdio(false); 
	long T,R,C;
    cin >> T;
    
	for(long t = 0; t < T; t++){
        cin >> R;
        cin >> C;
        long s,l,X,Y;
        bool possible = true;

        vector<long> vecx, vecy;
        long x, y;
        if(C>R){
            l = C;
            s = R;
        } else {
            l = R;
            s = C;
        }
        if (l <= 3) {
            cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
        } else if (l == 4 and s == 2){
            cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
        } else {
            if (s == 3){
                X = l;
                Y = s;
                x = 2;
                vector<long> stuff = {2,0,3,1,4,100};
                for (long i = 0; i < X; i++){
                    jumps(x, vecx, vecy, X, Y);
                    if (l == 5) x = stuff[i+1];
                    else if (l == 4) x = (x+X-1) % X;
                    else x = (x+1) % X;
                }               
            }

            else if (s == 2) {
                X = l;
                Y = s;
                x = 0;
                for (long i = 0; i < X; i++){
                    jumps(x, vecx, vecy, X, Y);
                    if (X % 2 == 0){
                        x = (x+X-1) % X;
                    } else {
                        x = (x+4) % X;
                    }
                    
                }
            } else {
                // both diemsions are at least 4
                X = s;
                Y = l;
                if (X%2 == 0){
                    x = 0;
                    for (long i = 0; i < X; i++){
                        jumps(x, vecx, vecy, X, Y);
                        x = (x+X-1) % X;
                    }                    
                } else {
                    // X is odd
                    if (X == Y){
                        // X=Y which can cause issues with diagonals
                        x = 0;
                        for (long i = 0; i < X; i++){
                            jumps(x, vecx, vecy, X, Y);
                            x = (x+1) % X;
                        }                            
                    } else {
                        // X is odd and we don't have to worry about diagonals
                        long x_dest = ((Y-1) * 2) % X;
                        long add = 2;
                        if (x_dest == 2) {
                            add = 4;
                        }
                        x = 0;
                        for (long i = 0; i < X; i++){
                            jumps(x, vecx, vecy, X, Y);
                            x = (x+add) % X;
                        }                             
                    }
                    

                }
            }

            long max_x = 0;
            for (long x: vecx){
                if(x > max_x) max_x = x;
            }
            max_x++;

            long x, y;
            long x_before = 100;
            long y_before = 1000;

            cout << "Case #" << t+1 << ": " << "POSSIBLE" << endl;
            for (long i = 0; i < vecx.size(); i++){
                x = vecx[i];
                y = vecy[i];
                if (x == x_before) cout << "failx";
                if (y == y_before) cout << "faily";
                if (x-x_before == y - y_before || x-x_before == y_before - y) cout << "faildiag";
                x_before = x;
                y_before = y;


                if (max_x == R) {
                    cout << vecx[i]+1 << " " << vecy[i]+1 << endl;
                } else {
                    cout << vecy[i]+1 << " " << vecx[i]+1 << endl;
                }
            }   

        }


    }
}