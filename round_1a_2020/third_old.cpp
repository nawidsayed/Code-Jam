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
	long T;
    cin >> T;
    for (long t = 0; t<T; t++){
        long R,C;
        cin >> R;
        cin >> C;

        long arr[R][C];
        long arr_next[R][C];

        for (long r = 0; r<R; r++){
            for (long c = 0; c<C; c++){
                cin >> arr[r][c];
            }
        }


        long upper[R][C];
        long lower[R][C];
        long lefter[R][C];
        long righter[R][C];

        for (long r = 0; r<R; r++){
            for (long c = 0; c<C; c++){
                if (r != R-1) {
                    lower[r][c] = r+1;
                } else {
                    lower[r][c] = -1;
                }
                if (r != 0) {
                    upper[r][c] = r-1;
                } else {
                    upper[r][c] = -1;
                }


                if (c != C-1) {
                    righter[r][c] = c+1;
                } else {
                    righter[r][c] = -1;
                }
                if (c != 0) {
                    lefter[r][c] = c-1;
                } else {
                    lefter[r][c] = -1;
                }

            }
        }


        long sum = 0;
        long cur = -1;
        while (true) {

            cout << "printer" << endl;
            for (long r = 0; r<R; r++){
                for (long c = 0; c<C; c++){
                    cout << arr[r][c] << " ";
                }
                cout << endl;
            }


            cout << "lefter" << endl;
            for (long r = 0; r<R; r++){
                for (long c = 0; c<C; c++){
                    cout << lefter[r][c] << " ";
                }
                cout << endl;
            }


            cout << "righter" << endl;
            for (long r = 0; r<R; r++){
                for (long c = 0; c<C; c++){
                    cout << righter[r][c] << " ";
                }
                cout << endl;
            }


            long next = 0;
            for (long r = 0; r<R; r++){
                for (long c = 0; c<C; c++){
                    next += arr[r][c];
                }
            }
            if (next == cur) {
                break;
            } else {
                cur = next;
                sum += cur; 
                long row, col;

                for (long r = 0; r<R; r++){
                    for (long c = 0; c<C; c++){
                        arr_next[r][c] = arr[r][c];
                    }
                }


                for (long r = 0; r<R; r++){
                    for (long c = 0; c<C; c++){
                        long sumNeigh = 0;
                        long countNeigh = 0;
                        
                        row = lower[r][c];
                        if (row != -1) {
                            sumNeigh += arr[row][c];
                            countNeigh++;
                        }
                        row = upper[r][c];
                        if (row != -1) {
                            sumNeigh += arr[row][c];
                            countNeigh++;
                        }
                        col = righter[r][c];
                        if (col != -1) {
                            sumNeigh += arr[r][col];
                            countNeigh++;
                        }
                        col = lefter[r][c];        
                        if (col != -1) {
                            sumNeigh += arr[r][col];
                            countNeigh++;
                        }                     

                        if (sumNeigh > arr[r][c] * countNeigh) {
                            arr_next[r][c] = 0;
                        } 

                    }
                }

                for (long r = 0; r<R; r++){
                    for (long c = 0; c<C; c++){
                        if (arr[r][c] != arr_next[r][c]){
                            row = lower[r][c];
                            if (row > -1) upper[row][c] = upper[r][c];

                            col = righter[r][c];
                            if (col > -1) lefter[r][col] = lefter[r][c];


                            // row = upper[r][c];
                            // lower[row][c] = lower[r][c];

                            // col = lefter[r][c];
                            // righter[r][col] = righter[r][c];
                        }
                    }
                }

                for (long r = R-1; r>=0; r--){
                    for (long c = C-1; c>=0; c--){
                        if (arr[r][c] != arr_next[r][c]){
                            row = upper[r][c];
                            if (row > -1) lower[row][c] = lower[r][c];

                            col = lefter[r][c];
                            if (col > -1) righter[r][col] = righter[r][c];


                            // row = lower[r][c];
                            // upper[row][c] = upper[r][c];

                            // col = righter[r][c];
                            // lefter[r][col] = lefter[r][c];
                        }
                    }
                }


                for (long r = 0; r<R; r++){
                    for (long c = 0; c<C; c++){                
                        arr[r][c] = arr_next[r][c];
                    }
                }
            }
        }

        cout << "Case #" << t+1 << ": "<< sum << endl;  
    }
}