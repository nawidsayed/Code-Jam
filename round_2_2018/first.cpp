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


vector<char> push_state(vl &state){
    long C = state.size();
    vl new_state(C,0);
    vector<char> layer(C,'.');
    long k;
    long lo,hi;
    long counter = 0;
    FOR(c,0,C){
        k = state[c];
        counter+=k;
        if (k >= 1){
            lo = min(k-1,1L);
            hi = k-lo;
            // when we are leftmost
            if (c==0){
                new_state[0] += hi;
                new_state[1] += lo;
                if (lo != 0)layer[1] = '/';
            }
            else if (c == C-1){
                if (not new_state[c-1]){
                    new_state[c-1] += k-1;
                    new_state[c] += 1;
                    if (k-1 != 0) layer[c-1] = '\\';
                } else {
                    new_state[c] += k;
                }                
            }
            // when we are inbetween 
            else {
                if (not new_state[c-1]){
                    if(k>=3 && counter-1>c){
                        new_state[c-1] += k-2;
                        new_state[c] += 1;
                        new_state[c+1] += 1;
                        layer[c-1] = '\\';
                        layer[c+1] = '/';
                    }
                    else {
                        new_state[c-1] += hi;
                        new_state[c] += lo;
                        layer[c-1] = '\\';
                    }
                } 
                else if (not new_state[c]){
                    if (counter-1 > c){
                        new_state[c] += hi;
                        new_state[c+1] += lo;
                        layer[c+1] = '/';
                    }
                    else {
                        new_state[c] += k;
                    }                     
                } else {
                    new_state[c+1] += k;
                    layer[c+1] = '/';
                }

            }
        }
    }
    state = new_state; 
    return layer;
}

void print_game(vector<vector<char>> game, long num_layers){
    reverse(all(game));
    long layer_ind = 0;
    for (vector<char> layer: game) {
        for (char c: layer) cout<<c;
        cout << endl;
        layer_ind++;
        if (layer_ind == num_layers) break;
    }
}

long solve(long t){
    long C;
    cin >> C;
    vl state(C);
    FOR(c,0,C) cin >> state[c];

    if (not state[0] or not state[C-1]){
        cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<vector<char>> game(C,vector<char>(C,'.'));

    vector<pll> mapping;

    long indexUpper = 0;
    long indexLower = 0;
    for(long k: state){
        while (k!=0){
            mapping.push_back(make_pair(indexUpper, indexLower));
            indexUpper++;
            k--;
        }
        indexLower++;
    }
    long max_diff = -1;
    long upper, lower;
    for (pll p: mapping){
        upper = p.first;
        lower = p.second;
        max_diff = max(abs(upper-lower), max_diff);
        if(upper < lower){
            FOR(i,0,lower-upper){
                game[C-1-i][upper+i] = '\\';
            }
        }
        if (lower < upper){
            FOR(i,0,upper-lower){
                game[C-1-i][upper-i] = '/';
            }
        }
    }
    long num_layers = max_diff+1;


    cout << "Case #" << t+1 << ": " << num_layers << endl;
    print_game(game, num_layers);

    return 0;   
}

int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}