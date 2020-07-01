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

#define print(...) _dbg(#__VA_ARGS__, __VA_ARGS__);
    
void send(long k){
    cout << k+1 << endl;
}

char read(){
    char c;
    cin >> c;
    return c;
}

long solve(long t){
    vector<string> perms(119, "ZZZZZ");
    string out = "ZZZZZ";
    map<char, long> counts;
    char c;
    FOR(k,0,119){
        send(k*5);
        c = read();
        perms[k][0] = c;
        counts[c] += 1;
    }
    vector<pair<long, char>> counts_inv;
    for (auto p: counts) counts_inv.push_back(make_pair(p.second, p.first));

    pair<long, char> mini = MIN(counts_inv);
    char missing = mini.second;

    out[0] = missing;

    vector<long>indices;
    FOR(k,0,119){
        if (perms[k][0] == missing){
            indices.push_back(k);
        }
    }

    FOR(i,1,5){
        counts.erase(missing);
        for (long k: indices){
            send(k*5+i);
            c = read();
            perms[k][i] = c;
            counts[c] += 1;
        }
        vector<pair<long, char>> counts_inv;
        for (auto p: counts) counts_inv.push_back(make_pair(p.second, p.first));

        pair<long, char> mini = MIN(counts_inv);
        missing = mini.second;

        out[i] = missing;

        vl indices_next;
        for (long k: indices){
            if (perms[k][i] == missing)indices_next.push_back(k);
        }
        indices = indices_next;

    }

    cout << out << endl;
    read();
    return 0;
}


int main(){
    long T,F;
    cin >> T;
    cin >> F;
    FOR(t,0,T) solve(t);
}