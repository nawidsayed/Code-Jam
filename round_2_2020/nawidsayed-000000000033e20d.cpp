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

pll sub(pll p1,pll p2){
    return make_pair(p1.first-p2.first, p1.second-p2.second);
}

long gcd(long a, long b){
    // careful, will return negative factors for negative arguments
    if (b == 0) return a;
    return gcd(b, a%b);
}

pll reduce(pll p){
    long fac = gcd(abs(p.first), abs(p.second));
    return make_pair(p.first / fac, p.second / fac);
}

pll firstPos(pll p){
    if (p.first == 0){
        if (p.second < 0) return make_pair(p.first, p.second * -1);
        else return p;
    } 
    if (p.first < 0){
        return make_pair(p.first * -1, p.second * -1);
    }
    return p;
}

long solve(long t){
    long N;
    cin >> N;

    if (N == 1){
        cout << "Case #" << t+1 << ": " << 1 << endl;
        return 0;  
    }

    vector<pll> holes;
    long x, y;
    FOR(n,0,N){
        cin >> x >> y;
        holes.push_back({x,y});
    }

    map<pll, set<long>> fracs;

    FOR(n,1,N){
        FOR(k,0,n){
            pll dir = sub(holes[n], holes[k]);
            pll v = firstPos(reduce(dir));
            fracs[v].insert(n);
            fracs[v].insert(k);
        }
    }

    long bestSize = -1;
    long curSize;
    pll bestFrac, curFrac;

    for (auto p: fracs){
        curFrac = p.first;
        curSize = p.second.size();
        if (curSize > bestSize){
            bestSize = curSize;
            bestFrac = curFrac;
        }
    }

    long effSize = bestSize - (bestSize % 2);
    long ans = min(effSize+2, N);

    cout << "Case #" << t+1 << ": " << ans << endl;
    return 0;
}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}