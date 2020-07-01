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
// always assume the worst :D use MAX and MIN for boundaries of long
// long a = 1; max(0,a); fails as max is on long and int
// for interactove problems write a function "query", which sends and reads at the same time
// Usually copies are inserted into containers or functions, pass by reference if needed
// Erasing in a container by iterator causes errors in g++6.3 e.g. list.erase(iter), use iter++ and account for increment 
// Be aware of functions with mod returning negative remainders
// print(...) macro can slow down the program

void update_intervals(map<double,double> &intervals){
    map<double,double> new_intervals;
    pair<double,double> p = *intervals.begin();
    pair<double,double> q;
    for (auto it = next(intervals.begin()); it != intervals.end(); it++){
        q = *it;
        if(p.second >= q.first){
            p.second = max(p.second, q.second);
        } else {
            new_intervals.insert(p);
            p = q;
        }
    }
    new_intervals.insert(p);
    intervals = new_intervals;
}

long solve(long t){
    long N;
    double P;
    cin >> N;
    cin >> P;
    vector<pll> cookies(N);
    long w,h;
    double perimeter = 0;
    FOR(n,0,N){
        cin >> w;
        cin >> h;
        cookies[n] = make_pair(w,h);
        perimeter += 2*w + 2*h;
    }

    map<double, double> intervals;
    intervals.insert(make_pair(perimeter, perimeter));

    double minc, maxc;

    for(pll cookie: cookies){
        minc = 2.0 * min(cookie.first, cookie.second);
        maxc = 2.0 * sqrt((double)cookie.first * cookie.first + cookie.second * cookie.second);

        map<double, double> new_intervals;

        for (pair<double, double> interval: intervals){
            new_intervals.insert(interval);
            new_intervals.insert(make_pair(interval.first+minc, interval.second+maxc));
        }
        intervals = new_intervals;
        // print("before")
        // for (auto p: intervals) print(p.first, p.second)

        update_intervals(intervals);
        // print("after")
        // for (auto p: intervals) print(p.first, p.second)
    }
    double best = -1;

    for(pair<double,double> p: intervals){
        if (p.first > P) break;
        if (p.first <= P and p.second >= P){
            best = P;
            break;
        } else {
            best = max(best, p.second);
        }
    }
    cout << fixed;
    cout << setprecision(6);
    cout << "Case #" << t+1 << ": " << best << endl;

    return 0;
}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);

}