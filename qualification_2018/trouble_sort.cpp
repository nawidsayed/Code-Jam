#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

// Trouble Sort sorts independently the even and odd indice entries of an array. 

int main(){
    // Speeds up input reading.
    ios_base::sync_with_stdio(false); 
    long T,n;
    cin >> T;
    for(long t = 0; t < T; t++){
        cin >> n;
        int an = n/2;
        int bn = an;
        if(n%2 == 1) an++;
        int a[an];
        int b[bn];
        // Splitting input according to even and odd indices.
        for(int i=0; i<n; i++){
            if (i % 2 ==0) cin >> a[i/2];
            else cin >> b[i/2];
        }
        sort(a, a+an);
        sort(b, b+bn);
        int arr[n];
        // Merging sorted arrays back.
        for(int i=0; i<n; i++){
            if (i % 2 ==0) arr[i] = a[i/2];
            else arr[i] = b[i/2];
        }
        // Finding first error in merged array.
        int broken = -1;
        for(int i = 0; i<n-1; i++){
            if (arr[i] > arr[i+1]){
                broken = i;
                break;                
            }
        }
        // Output.
        if(broken != -1) cout << "Case #" << t+1 << ": " << broken << endl;
        else  cout << "Case #" << t+1 << ": OK" << endl;
    }
}