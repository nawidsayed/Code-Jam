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

long maxrb = 501;

pll get_rb(long r, long b){
    return make_pair(r*(r+1)/2 * (b+1), b*(b+1)/2 * (r+1));
}

void push_state(pll pair, ml &state){
    ml state_next(maxrb, vl(maxrb, 0));

    long r_new = pair.first;
    long b_new = pair.second;

    FOR(r,0,maxrb){
        FOR(b,0,maxrb){
            if (r < r_new || b < b_new){
                state_next[r][b] = state[r][b];
            }
            else{
                state_next[r][b] = max(state[r][b], 1+state[r-r_new][b-b_new]);
            }
            
        }
    }

    state = state_next;

}


long solve(long t, ml &state){
    long R,B;
    cin >> R;
    cin >> B;
    long solution = state[R][B] - 1;

    cout << "Case #" << t+1 << ": " << solution << endl;
    return 0;
}

void func(){throw 1.4;}

int main(){
    
    // vector<pll> pairs;

    // FOR(r,0,50){
    //     FOR(b,0,50){
    //         pll numrb = get_rb(r,b);
    //         if (numrb.first < maxrb and numrb.second < maxrb) pairs.push_back(make_pair(r,b));
    //     }
    // }


    // ml state(maxrb, vl(maxrb, 0));

    // for (auto p: pairs){
    //     push_state(p, state);
    // }


    // long T;
    // cin >> T;
    // FOR(t,0,T) solve(t,state);

    try{
        func();
    }
    catch(double e) {
        print(e)
    }

    vl a{1,2,3};

    print(a[2])

}