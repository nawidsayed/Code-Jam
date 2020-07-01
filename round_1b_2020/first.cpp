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



long solve(long t){
    long x,y;
    cin >> x;
    cin >> y;

    bool xneg = false;
    bool yneg = false;

    if (x < 0) {
        xneg = true;
        x *= -1;
    }

    if (y < 0) {
        yneg = true;
        y *= -1;
    }

    long rx, ry;
    long nrx, nry;
    string out;

    long xn, yn;

    while(x != 0 or y!=0){

        rx = x%2;
        ry = y%2;
        xn = x / 2;
        yn = y / 2;

        if(rx == ry){
            cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
            return 0;
        }
        nrx = xn % 2;
        nry = yn % 2;
        if(rx){
            if(nrx == nry and (x+y) != 1){
                if (xneg) {out += 'E';}
                else {out += 'W';}
                x++;
            } else {
                if (xneg) {out += 'W';}
                else {out += 'E';}
                x--;
            }
        } 
        else {
            if(nrx == nry and (x+y) != 1){
                if (yneg) {out += 'N';}
                else {out += 'S';}
                y++;
            } else {
                if (yneg) {out += 'S';}
                else {out += 'N';}
                y--;
            }            
        }
        x /= 2;
        y /= 2;


    }

    cout << "Case #" << t+1 << ": " << out << endl;
    return 0;
}

int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}