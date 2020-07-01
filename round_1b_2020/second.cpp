#pragma GCC optimize ("O3")

#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <unordered_map>
#include <numeric>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORR(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define all(x) (x).begin(), (x).end()

#define MAX(cont) *max_element(all((cont))) 
#define MIN(cont) *min_element(all((cont))) 
#define ARGMAX(cont) max_element(all((cont))) - (cont).begin()
#define ARGMIN(cont) min_element(all((cont))) - (cont).begin()

#define MAXLONG 9223372036854775807L
#define MINLONG -9223372036854775808L

typedef pair<long, long> pll;
typedef vector<long> vl;
typedef vector<vector<long>> ml;

template<typename T> 
using matrix = vector<vector<T>>;

template<class Container>
void printc(const Container &cont){
    for (auto e: cont) cout << e << " "; cout << endl;
}

template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH> void _dbg(const char *sdbg, const vector<TH> &vec){ 
    cerr<<sdbg<<'=';
    for (TH e: vec) cerr << e << " "; cerr << endl; 
}
template<class TH> void _dbg(const char *sdbg, const vector<vector<TH>> &mat){ 
    cerr<<sdbg<<'='<< endl;
    for(vector<TH> vec: mat){for(TH e: vec) cerr << e << " "; cerr << endl;}
}
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
    while(*sdbg!=',')cerr<<*sdbg++;
    cerr<<'='<<h<<','<<' '; _dbg(sdbg+1, a...);
}
#define print(...) _dbg(#__VA_ARGS__, __VA_ARGS__);

// Things to be aware of:
// map is always ordered according to key
// always assume the worst :D use MAX and MIN for boundaries of long
// long a = 1; max(0,a); fails as max is on long and int
// for interactove problems write a function "query", which sends and reads at the same time
// Usually copies are inserted into containers or functions, pass by reference if needed
// Erasing in a container by iterator causes errors in g++6.3 e.g. list.erase(iter), use iter++ and account for increment 
// Be aware of functions with mod returning negative remainders
// print(...) macro can slow down the program

long fac = 1e9;

long query(long x, long y){
    cout << x << " " << y << endl;
    string s;
    cin >> s;
    print(x,y,s)
    if(s == "CENTER") return 2;
    if(s == "HIT") return 1;
    if(s == "MISS") return 0;
    else {print("unknown"); return -1;}
}

// assuming lo is in board
long binarylox(long lo, long hi, long y){
    long avg;
    long queryres;
    while(hi-lo > 1){
        avg = (lo+hi) / 2;
        queryres = query(avg, y);
        if (queryres == 2) return fac + 2;
        if (queryres >= 1){
            lo = avg + 1;
        } else {
            hi = avg;
        }
    }
    return lo;
}

// assuming lo is in board
long binaryhix(long lo, long hi, long y){
    long avg;
    long queryres;
    while(hi-lo > 1){
        avg = (lo+hi) / 2;
        queryres = query(avg, y);
        if (queryres == 2) return fac + 2;
        if (queryres == 0){
            lo = avg + 1;
        } else {
            hi = avg;
        }
    }
    return lo;
}

// assuming lo is in board
long binaryloy(long lo, long hi, long x){
    long avg;
    long queryres;
    while(hi-lo > 1){
        avg = (lo+hi) / 2;
        queryres = query(x, avg);
        if (queryres == 2) return fac + 2;
        if (queryres >= 1){
            lo = avg + 1;
        } else {
            hi = avg;
        }
    }
    return lo;
}

// assuming lo is in board
long binaryhiy(long lo, long hi, long x){
    long avg;
    long queryres;
    while(hi-lo > 1){
        avg = (lo+hi) / 2;
        queryres = query(x, avg);
        if (queryres == 2) return fac + 2;
        if (queryres == 0){
            lo = avg + 1;
        } else {
            hi = avg;
        }
    }
    return lo;
}

long solve(long t){
    long fachalf = fac / 2;

    vl initResults;
    long xf, yf;
    long queryres;
    FOR(x, -1, 2){
        FOR(y, -1, 2){
            queryres = query(x*fachalf, y*fachalf);
            if(queryres == 1) {
                xf = x*fachalf;
                yf = y*fachalf;
            }
            if (queryres == 2) return 0;

        }    
    }


    print(xf, yf)

    long xhi = binarylox(xf, fac, yf);
    if (xhi == fac + 2) return 0;
    long xlo = binaryhix(-fac, xf, yf);
    if (xlo == fac + 2) return 0;

    long yhi = binaryloy(yf, fac, xf);
    if (yhi == fac + 2) return 0;
    long ylo = binaryhiy(-fac, yf, xf);
    if (ylo == fac + 2) return 0;

    print(xhi)
    print(xlo)
    print(yhi)
    print(ylo)

    long xcenter = (xhi + xlo) / 2;
    long ycenter = (yhi + ylo) / 2;

    long result;

    FOR(x, -3,4){
        FOR(y, -3, 4){
            result = query(xcenter+x, ycenter+y);
            if (result == 2) return 0;
        }
    }

    // TODO incase of +- 1 garbage, just query all of them



    print("I shouldnt get here")


    return 0;
}

int main(){
    long T;
    cin >> T;
    long A,B;
    cin >> A;
    cin >> B;
    FOR(t,0,T) solve(t);
}