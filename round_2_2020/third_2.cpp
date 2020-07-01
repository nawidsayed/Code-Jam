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
    if (b == 0) return max(a,1L);
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

long solve(vector <pll> holes){

    long N = holes.size();

    if (N == 1){
        return 1;  
    }

    long x, y;

    map<pll, set<long>> fracs;


    FOR(n,1,N){
        FOR(k,0,n){
            pll dir = sub(holes[n], holes[k]);
            pll v = firstPos(reduce(dir));
            // if (!fracs.count(v)) fracs[v] = {};
            // if (!(fracs[v].count(n) + fracs[v].count(k)))
            fracs[v].insert(n);
            fracs[v].insert(k);
        }
    }


    // for (auto p: fracs){
    //     for (long k: p.second) cout << k << " ";
    //     cout << endl;
    // }

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

    return ans;
}

int solve2(vector<pll> holes) {
    int n = holes.size();

    vector<long long> x(n);
    vector<long long> y(n);
    for (int i = 0; i < n; i++) {
        x[i] = holes[i].first;
        y[i] = holes[i].second;
    }
    int ans = min(n, 2);
    for (int i1 = 0; i1 < n; i1++) {
      for (int i2 = i1 + 1; i2 < n; i2++) {
        long long a = y[i2] - y[i1];
        long long b = x[i1] - x[i2];
        long long c = -a * x[i1] - b * y[i1];
        vector<long long> z(n);
        for (int i = 0; i < n; i++) {
          z[i] = a * x[i] + b * y[i] + c;
        }
        sort(z.begin(), z.end());
        int add = 0;
        int k1 = 0;
        int k3 = 0;
        int beg = 0;
        while (beg < n) {
          int end = beg;
          while (end + 1 < n && z[end + 1] == z[end]) {
            ++end;
          }
          int cnt = end - beg + 1;
          if (cnt % 2 == 0) {
            add += cnt;
          } else {
            if (cnt == 1) {
              k1 += 1;
            } else {
              add += cnt - 3;
              k3 += 1;
            }
          }
          beg = end + 1;
        }
        while (k3 >= 2) {
          add += 6;
          k3 -= 2;
        }
        if (k3 == 0) {
          add += min(k1, 2);
        } else {
          add += 3 + min(k1, 1);
        }
        ans = max(ans, add);
      }
    }
    ans = min(ans, n);
    return ans;
}


int main(){
    long ans, ans2;
    long r1,r2;
    
    long mod = 1000000000000;

    FOR(i,0,100000){
        set<pll> points;
        FOR(n,0,7){
            r1 = rand() % (2*mod+1) - mod;
            r2 = rand() % (2*mod+1) - mod;
            points.insert({r1,r2});
        }
        vector<pll> holes;
        for(pll p: points) holes.push_back(p);

        ans = solve(holes);
        ans2 = solve2(holes);

        if(ans - ans2 != 0) print("esdfsdfrroas;fhjkadls;fjk", ans, ans2)    
        if (i%10000 == 0){
            print(ans, ans2, holes.size())
        }    

    }

     

}
