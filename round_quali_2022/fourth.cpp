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
#include <bitset>
#include <queue>
using namespace std;

#define FOR(i,a,b) for (long i = (a); i < (b); i++)
#define FORR(i,a,b) for (long i = (b)-1; i >= (a); i--)
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
// In case of circular function references, declare an empty function at the top e.g. long func(long k);
// reassigning containers, e.g. vl vec2 = vec makes a copy.
// get iterator pointer via &(*iter)
// use g++sane for debugging, it catches array out of bound shenanigans
// you can do an ultimate return with a try / catch block 
// map is always ordered according to key
// always assume the worst :D use MAX and MIN for boundaries of long
// long a = 1; max(0,a); fails as max is on long and int
// for interactove problems write a function "query", which sends and reads at the same time
// Usually copies are inserted into containers or functions, pass by reference if needed
// Erasing in a container by iterator causes errors in g++6.3 e.g. list.erase(iter), use iter++ and account for increment 
// Be aware of functions with mod returning negative remainders
// print(...) macro can slow down the program

void func(long i, vector<vl> &parents, vl &minis, vl &v) {
    long minimum = MAXLONG;
    for(long p: parents[i]) {
        func(p, parents, minis, v);
        minimum = min(minimum, minis[p]);
    }
    if (minimum == MAXLONG) {
        minimum = 0;
    }   
    minis[i] = max(v[i], minimum);
}

void func2(long i, long maxi, vector<vl> &parents, vl &minis, vl &v, long &total) {
    if (parents[i].size() == 0) {
        total += maxi;
    } else {
        long mini_parent;
        long best_mini = MAXLONG;
        long cur;
        for (long p: parents[i]){
            cur = minis[p];
            if (cur < best_mini) {
                best_mini = cur;
                mini_parent = p;
            }
        }
        for (long p: parents[i]) {
            long maxip = v[p];
            if (p == mini_parent) maxip = max(maxi, maxip);
            func2(p, maxip, parents, minis, v, total);
        }
    }
}

long solve(long t){
    long N;
    cin >> N;
    vl v(N);
    FOR(i,0,N) cin >> v[i];
    vector<vl> parents(N);
    vl roots;
    long c;
    FOR(i,0,N) {
        cin >> c;
        c--;
        if (c == -1) roots.push_back(i);
        else parents[c].push_back(i);
    }

    vl minis(N);
    for(long r: roots) {
        func(r, parents, minis, v);
    }

    long total = 0;
    for(long r: roots) {
        func2(r, v[r], parents, minis, v, total);    
    }

    cout << "Case #" << t+1 << ": " << total << endl;
    return 0;

    
}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}