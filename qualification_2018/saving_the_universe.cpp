#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

// Best strategy is to swap the last possible CS pair. 
// We try to reduce damage below D until we cant swap anymore, in that case we retrun IMPOSSIBLE 
// S: 1, C: 0.

// Apparently std::swap is broken...
void myswap(int *arr, int i){
    int temp = arr[i];
    arr[i] = arr[i+1];
    arr[i+1] = temp;
}

// Swaps the last possible CS pair and returns true, if no swap it returns false.  
bool swapper(int *arr, int l){
    bool can_swap = false;
    for(int i = l-1; i>=0; i--){
        if(arr[i]){
            can_swap = true;
        }
        if(can_swap and not arr[i]){
            myswap(arr, i);
            return true;
        }
    }
    return false;
}

// Calculates the current damage of configuration.
long damage(int *arr, int l){
    long sum = 0;
    long cur = 1;
    for(int i = 0; i < l; i++){
        if(arr[i]){
            sum += cur;
        } else {
            cur *= 2;
        }
    }
    return sum;
}

int main(){
    // Speeds up input reading.
    ios_base::sync_with_stdio(false); 
    int T,d,l;
    char c;
    string s; 
    cin >> T;
    for(long t = 0; t < T; t++){
        cin >> d;
        cin >> s;
        l = s.length();
        int *arr = new int[l];
        for(int i = 0; i < l; i++){
            if(s[i] == 'C'){
                arr[i] = 0;
            } else {
                arr[i] = 1;
            }
        }
        int swaps = 0;
        bool possible = true;
        while(possible and damage(arr,l) > d){
            possible = swapper(arr,l);
            swaps++;
        }
        // Output.
        if(not possible) cout << "Case #" << t+1 << ": IMPOSSIBLE" << endl;
        else cout << "Case #" << t+1 << ": " << swaps << endl;
    }
    return 0;
}