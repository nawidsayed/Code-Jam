#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

// We utilize the fact that the projection area on the surface is equal to the projection length
// on the surface normal. The solution is derived from using basic gemoetric arguments.

int main(){
    // Speeds up input reading.
    ios_base::sync_with_stdio(false); 
    double pi = 3.141592653589793238463;
    double sq2 = sqrt(2);
    // Distance from center cube to one of its vertices.
    double l = sqrt(0.75);
    long T;
    double a, b, alpha, beta, gamma;
    cin >> T;
    for(long t = 0; t < T; t++){
        cin >> a;
        b = a/2;
        alpha = asin(b/l);
        beta = asin(0.5/l);
        gamma = alpha - beta;
        double vs = sin(gamma);
        double vc = cos(gamma);
        double h = sq2/4;
        double p1[] = {-vs/2, vc/2, 0};
        double p2[] = {vc*h, vs*h, h};
        double p3[] = {-vc*h, -vs*h, h};
        cout.precision(15);
        cout << "Case #" << t+1 << ":" << endl;
        cout << p1[0] << " " << p1[1] << " " << p1[2] << endl;  
        cout << p2[0] << " " << p2[1] << " " << p2[2] << endl;  
        cout << p3[0] << " " << p3[1] << " " << p3[2] << endl;  
    }
}