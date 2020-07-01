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
#include <stack>
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
// Accesing a map or set with i = map[k] will add that element into the set with default value
// Always make sure to read everything in before printing and returning a solution!!!!!
// In case of circular function references, declare an empty function at the top e.g. long func(long k);
// reassigning containers, e.g. vl vec2 = vec makes a copy.
// get iterator pointer via &(*iter)
// use g++sane for debugging, it catches array out of bound shenanigans
// you can do an ultimate return with a try / catch block, use throw 1;
// map is always ordered according to key
// always assume the worst :D use MAX and MIN for boundaries of long
// long a = 1; max(0,a); fails as max is on long and int
// for interactove problems write a function "query", which sends and reads at the same time
// Usually copies are inserted into containers or functions, pass by reference if needed
// Erasing in a container by iterator causes errors in g++6.3 e.g. list.erase(iter), use iter++ and account for increment 
// Be aware of functions with mod returning negative remainders
// print(...) macro can slow down the program


long mod = 1000000007;


vl mass, mass2;
stack<long> finished;

void visit(long n, vector<vl> &out, vl &visited, stack<long> &finished){
    if (visited[n]) return;
    visited[n] = 1;
    for (long c: out[n]) visit(c, out, visited, finished);
    finished.push(n);
}

void assign(long n, long u, vector<vl> &in, vl &visited, vl &who){
    if (!visited[n]) return;
    visited[n] = 0;
    who[n] = u;
    for (long p: in[n]) assign(p, u, in, visited, who);
}

vl strongly_connected(vector<vl> &in, vector<vl> &out){
    long num_nodes = in.size(); // make sure in contains parents for all nodes
    vl visited(num_nodes); 
    vl who(num_nodes);
    stack<long> finished;

    FOR(n,0,num_nodes) visit(n, out, visited, finished);
    while(!finished.empty()) {
        long n = finished.top(); 
        finished.pop();
        assign(n,n, in, visited, who);
    }   
    return who;    
}


void back(long n, vector<vector<long>> &in, vector<vector<long>> &out, vl &visited, vl &loop){
    // print(n)
    if (visited[n]) return;
    visited[n] = 1;
    for (long p: in[n]){
        back(p, in, out, visited, loop);
    }

    if (loop[n]>0 && mass2[n]) throw 1;

    for (long c: out[n]){
        mass[c] = (mass[c] + mass[n]) % mod;
        mass2[c] = max(mass2[c], mass2[n]);
    }
    mass[n] = 0;
    mass2[n] = 0;
}

long solve(long t){
    long M;
    cin >> M;
    vector<vl> in(M);
    vector<vl> out(M);
    mass = vl(M);
    mass2 = vl(M);
    

    long l,r;
    FOR(m,0,M){
        cin >> l >> r, l--, r--;
        in[l].push_back(m);
        in[r].push_back(m);
        out[m] = vl({l,r});
    }

    FOR(m,0,M) cin >> mass[m];

    // print(in)
    // print(out)
    // print(mass)


    vl who = strongly_connected(in, out);
    long u, k;
    vl loop(M,1);

    vector<vector<long>> ins(M), outs(M);


    FOR(m,0,M){
        u = who[m];
        long temp = mass[m];
        mass[u] += temp;
        mass[m] -= temp;
        loop[u] --;


        FOR(i,0,in[m].size()) {
            k = who[in[m][i]];
            if (k != u) ins[u].push_back(k);
        }
        FOR(o,0,out[m].size()) {
            k = who[out[m][o]];
            if (k == u) loop[u]++;
            if (k != u) outs[u].push_back(k);
        }
    }
    FOR(m,0,M) loop[m] = loop[who[m]]; // TODO check if works without this line. It should

    
    FOR(m,0,M){
        mass2[m] = min(mass[m], 1L);
        mass[m] = mass[m]%mod;
    }


    vl visited(M);
    // for (auto s: ins) printc(s);
    
    // print(in)

    // print(mass)

    // print(who)


    try{
        for (long p: ins[0]){
            // print(p)
            back(p, ins, outs, visited, loop);    
        }
    }
    catch (int param){
        cout << "Case #" << t+1 << ": " << "UNBOUNDED" << endl;
        return 0;
    }

    if (mass2[0] > 0 && loop[0] > 1){
        cout << "Case #" << t+1 << ": " << "UNBOUNDED" << endl;
        return 0;        
    }
    // print(who)
    // print(mass)
    
    cout << "Case #" << t+1 << ": " << mass[0] << endl;
    return 0;
}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}