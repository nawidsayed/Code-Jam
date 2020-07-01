#pragma GCC optimize ("O3")

#include <sstream>
#include <iostream>
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

#define print(a) cout << (a) << endl;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORR(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define all(x) (x).begin(), (x).end()

#define MAX(cont) *max_element(all((cont))) 
#define MIN(cont) *min_element(all((cont))) 
#define ARGMAX(cont) max_element(all((cont))) - (cont).begin()
#define ARGMIN(cont) min_element(all((cont))) - (cont).begin()

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
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__);



long gcd(long a, long b){
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main(){
    long T,N;
    long c,j;
    cin >> T;
    FOR(t,0,T){
        cin >> N;
        vector<pll> molecules(N);
        FOR(n,0,N){
            cin>>c;
            cin>>j;
            molecules[n] = make_pair(c,j);
        }

        set<pll> ratios;

        pll p1, p2;
        long fac;
        FOR(i,0,N){
            p1 = molecules[i];
            FOR(k,0,i){
                p2 = molecules[k];

                c = p1.first - p2.first;
                j = p2.second - p1.second;

                fac = gcd(c,j);
                if (c*j > 0) ratios.insert(make_pair(c / fac, j / fac));
                

            }
        }
        ml mat(2, vl{1,2,3,4});
        cout << "Case #" << t+1 << ": " << ratios.size() + 1 << endl;
    }
}