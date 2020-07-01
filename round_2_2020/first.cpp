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

long tri(long n){
    return n*(n+1) / 2;
}

long trie(long n){
    return n*(n+1);
}

long trio(long n){
    return (n)*(n);
}

long solve(long t){
    long l,r;
    cin >> l >> r;

    long x = min(l,r);
    long y = max(l,r);

    bool isXleft = l<=r;

    long total = 0;


    long diff = y-x;
    if (diff){
        long first = max(0L, (long) sqrt(2*diff) - 2);

        FOR(i,0,6){
            if (tri(first+1) <= diff) first++;
            else break;
        }

        y -= tri(first);
        total += first;

        // print(x,y,total)
    }

    long sube = total / 2;
    long subo = (total+1) / 2;

    long final = max(0L, (long) sqrt(min(x,y) + trio(subo))-3);

    // print(final)

    long odds = final;
    long evens = final;


    long parity = total % 2;

    long x_old = x;
    long y_old = y;

    if (x == y){

        FOR(i,0,10){
            if(trio(odds+1) <= y + trio(subo)){odds++;}
            else break;
        }
        y -= trio(odds) - trio(subo);
        FOR(i,0,10){
            if(trie(evens+1) <= x + trie(sube)){evens++;}
        }
        x -= trie(evens) - trie(sube);
        
        if((!parity && isXleft) || (parity && !isXleft)) swap(x,y);
    }

    if (x_old<y_old){
        if (parity){
            FOR(i,0,10){
                if(trio(odds+1) <= x + trio(subo)){odds++;}
                else break;
            }
            x -= trio(odds) - trio(subo);
            FOR(i,0,10){
                if(trie(evens+1) <= y + trie(sube)){evens++;}
            }
            y -= trie(evens) - trie(sube);
        } else {
            FOR(i,0,10){
                if(trio(odds+1) <= y + trio(subo)){odds++;}
                else break;
            }
            y -= trio(odds) - trio(subo);
            FOR(i,0,10){
                if(trie(evens+1) <= x + trie(sube)){evens++;}
            }
            x -= trie(evens) - trie(sube);
        }        
    } 
    if(y_old<x_old){
        if (!parity){
            FOR(i,0,10){
                if(trio(odds+1) <= x + trio(subo)){odds++;}
                else break;
            }
            x -= trio(odds) - trio(subo);
            FOR(i,0,10){
                if(trie(evens+1) <= y + trie(sube)){evens++;}
            }
            y -= trie(evens) - trie(sube);
        } else {
            FOR(i,0,10){
                if(trio(odds+1) <= y + trio(subo)){odds++;}
                else break;
            }
            y -= trio(odds) - trio(subo);
            FOR(i,0,10){
                if(trie(evens+1) <= x + trie(sube)){evens++;}
            }
            x -= trie(evens) - trie(sube);
        }       
    }

    total += evens + odds - sube - subo;


    if (isXleft){
        l = x;
        r = y;
    } else {
        l = y;
        r = x;
    }
    // print(total, l, r);


    cout << "Case #" << t+1 << ": " << total << " " << l << " " << r << endl;
    return 0;
}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}