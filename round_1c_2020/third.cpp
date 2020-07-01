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

long gcd(long a, long b){
    // careful, will return negative factors for negative arguments
    if (b == 0) return a;
    return gcd(b, a%b);
}

pll reduce(pll frac){
    long fac = gcd(frac.first, frac.second);
    return make_pair(frac.first / fac, frac.second / fac);
}

pll compute_avg(pll f1, pll f2){
    long lcm = (f1.second / gcd(f1.second, f2.second)) * f2.second;
    long numerator = f1.first * lcm / f1.second + f2.first * lcm / f2.second;
    return reduce(make_pair(numerator, lcm*2));
}

long best_D(vl &vec, pll size){
    long total = 0;
    for(long a: vec){
        total += a * size.second / size.first;
    }

    return total;
}


long solve(long t){
    long N,D;
    cin >> N >> D;

    vl vec(N);
    FOR(n,0,N){
        cin >> vec[n];
    }

    pll frac;
    long k, s;
    set<pll> fracs;


    pll lo = make_pair(1,1e3);
    pll hi = make_pair(1e3,1);
    pll avg;
    long d;

    FOR(i,0,3000){
        avg = compute_avg(lo, hi);
        print(1.0*avg.first / avg.second)

        d = best_D(vec, avg);
        if (d >= D){
            lo = avg;
        }
        else{
            hi = avg;
        }
    }

    


    FOR(n,0,N){
        s = vec[n];
        FOR(k,1,51){
            frac = reduce(make_pair(s, k));
            fracs.insert(frac);
        }

    }

    cout << "Case #" << t+1 << ": " << -1 << endl;

    return 0;
}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}