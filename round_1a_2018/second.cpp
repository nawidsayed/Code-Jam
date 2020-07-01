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

long get_max_bits(const long time, const ml &data, const long R){
    vl bits;
    for(vl p: data){

        long bit = max(min(p[0], (time-p[2]) /p[1]),0L);
        bits.push_back(bit);
    }
    sort(all(bits));
    reverse(all(bits)); 
    long total = 0;
    FOR(i,0,R){
        total += bits[i];
    }
    return total;
}

long solve(long t){
    long R,B,C;
    cin>>R;
    cin>>B;
    cin>>C;
    
    ml data(C,vl(3,0));
    FOR(c,0,C){
        cin >> data[c][0];
        cin >> data[c][1];
        cin >> data[c][2];
    }

    
    long low = 0;
    long high = MAXLONG;
    long avg;
    long bits;

    while (high != low){
        avg = (high+low) /2;
        bits = get_max_bits(avg, data, R);
        if (bits < B)low = avg+1;
        else high =avg;
    }
    // print(low, high)
    cout << "Case #" << t+1 << ": " << high << endl;
    return 0;   
}

int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}