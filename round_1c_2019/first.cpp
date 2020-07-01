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
    

long solve(long t){
    long A;
    cin >> A;
    list<string> opps;
    string s;
    FOR(a,0,A){
        cin >> s;
        opps.push_back(s);
    }
    string out;
    FOR(k,0,500){
        set<char> moves;
        for(auto it = opps.begin(); it != opps.end(); it++){
            string opp = *it;
            char move = opp[k%opp.size()];
            moves.insert(move);
        }
        char counter;
        if (moves.size() == 3) {cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl; return 0;}
        
        else if (moves.size() == 2) {   
            if (moves.count('R')){
                if(moves.count('S')){
                    counter = 'R';
                } else counter = 'P';
            } else counter = 'S';
        }
        else if (moves.size() == 1){
            if (moves.count('R')) counter = 'P';
            if (moves.count('P')) counter = 'S';
            if (moves.count('S')) counter = 'R';
        }
        else {
            cout << "Case #" << t+1 << ": " << out << endl; return 0;
        }
        out += counter;
        char elim;
        if (counter == 'R') elim='S';
        else if (counter == 'P') elim='R';
        else if (counter == 'S') elim='P';
        for(auto it = opps.begin(); it != opps.end(); it++){

            string opp = *it;
            char move = opp[k%opp.size()];
            if (move == elim) {opps.erase(it++);it--;}
            
        }
    }
    cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl; return 0;
}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}