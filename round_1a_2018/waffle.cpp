#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <set>
#include <numeric>
using namespace std;



int main() {
    ios_base::sync_with_stdio(false); 
	long T,R,C,H,V;
    cin >> T;
	for(long t = 0; t < T; t++){
        cin >> R;
        cin >> C;
        cin >> H;
        cin >> V;
        long waffle[R][C];
        char s; 
        for (long r = 0; r < R; r++){
            for (long c = 0; c < C; c++){
                cin >> s;
                if (s == '.') waffle[r][c] = 0;
                else waffle[r][c] = 1;
            }    
        }

        long total = 0;
        for (long r = 0; r < R; r++){
            for (long c = 0; c < C; c++){
                total += waffle[r][c];
            }    
        }

        bool possible = true;

        // Is the total number of chips right?
        if (total %((H+1) * (V+1)) != 0){
            possible = false;
        } 

        // do the rows fit?
        vector<long> horizontal_cuts;
        long chocolate_per_piece = total / ((H+1) * (V+1));
        if (possible) {
            
            long waffle_rows[R];
            for (long r = 0; r < R; r++){
                long sum = 0;
                for (long c = 0; c < C; c++){
                    sum += waffle[r][c];
                }
                waffle_rows[r] = sum;    
            }


            
            long cur = 0;
            long thresh = chocolate_per_piece * (V+1);

            for (long r = 0; r < R; r++){
                cur += waffle_rows[r];
                if (cur == thresh){
                    horizontal_cuts.push_back(r+1);
                    cur = 0;
                } else if (cur > thresh){
                    possible = false;
                    break;
                }

            }           
        }


        // do the columns fit?
        vector<long> vertical_cuts;
        if (possible) {
            
            long waffle_columns[C];
            for (long c = 0; c < C; c++){
                long sum = 0;
                for (long r = 0; r < R; r++){
                    sum += waffle[r][c];
                }
                waffle_columns[c] = sum;    
            }


            
            long cur = 0;
            long thresh = chocolate_per_piece * (H+1);

            for (long c = 0; c < C; c++){
                cur += waffle_columns[c];
                if (cur == thresh){
                    vertical_cuts.push_back(c+1);
                    cur = 0;
                } else if (cur > thresh){
                    possible = false;
                    break;
                }
            }           
        }

        // Do both fit?
        if (possible){
            long lower = 0;
            for (long h: horizontal_cuts){
                long left = 0;
                for (long v: vertical_cuts){
                    long sum = 0;
                    for (long r = lower; r<h; r++){
                        for (long c = left; c<v; c++){
                            sum += waffle[r][c];
                        }
                    }
                    if (sum != chocolate_per_piece){
                        possible = false;
                        break;
                    }
                    left = v;    
                }
                lower = h;
            }
        }

        string out = "IMPOSSIBLE";
        if(possible) {out = "POSSIBLE";}

        cout << "Case #" << t+1 << ": "<< out << endl;  

    }
}