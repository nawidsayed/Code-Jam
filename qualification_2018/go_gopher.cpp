#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

// We prepare a strip of land with of 3 rows and 68 columns independently of the given input area. 
// We use offset O to prevent illegal array index error. 

const int R = 3;
const int C = 68;
const int O = 10;

// Declaring  soil cells.
int arr[R][C];

// Returns the number of prepared cells in a 3x3 square centered at r,c.
int prepared(int r,int c){
    int sum = 0;
    for(int i=r-1; i<=r+1; i++){
        for(int j=c-1; j<=c+1; j++){
            sum += arr[i][j];
        }
    }
    return sum;
}

int main() {
    // Speeds up input reading.
    ios_base::sync_with_stdio(false); 
    long T, a;
    cin >> T;
    for(long t = 0; t < T; t++){
        cin >> a;
        // Initializing soil cells to be unprepared.
        for(int r=0; r<R; r++){
            for(int c=0; c<C; c++){
                arr[r][c]=0;
            }
        }
        int i,j,best;
        while(true){
            // Upper bound for sum is 9.
            best = 10;
            int cur;
            int r = 1;
            // Finding column with the most unprepared cells.
            for(int c=1; c<C-1; c++){
                cur = prepared(r, c); 
                if(cur < best){
                    best = cur; 
                    i = r;
                    j = c;
                }
            }
            cout << i+O  << " " << j+O << endl;
            cin >> i;
            cin >> j;
            // Handling errors.
            if(i == -1){
                return 0;
            }
            // Going to the next case.
            if(i == 0){
                break;
            }
            i -= O;
            j -= O;
            // Preparing cell.
            arr[i][j] = 1;
        }
    }
}

