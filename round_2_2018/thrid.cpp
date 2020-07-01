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
#include <deque>
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

struct Maxflow{
    long source, sink;
    matrix<pll> destcap;
    deque<pll*> path;
    vector<bool> visited;

    // souce = n
    // sink = n+1
    Maxflow(long n){
        destcap = matrix<pll>(n+2);
        source = n;
        sink = n+1;
        visited = vector<bool>(n+2,0);
    }

    // from and to smaller than n
    void add_edge(long from, long to, long cap){
        destcap[from].push_back(make_pair(to, cap));
        destcap[to].push_back(make_pair(from, cap));
    }

    void add_edge_from_source(long to, long cap){
        destcap[source].push_back(make_pair(to, cap));
        destcap[to].push_back(make_pair(source, -MAXLONG));
    }

    void add_edge_to_sink(long from, long cap){
        destcap[from].push_back(make_pair(sink, cap));
        destcap[sink].push_back(make_pair(from, cap));
    }

    long dfs(long flow, long from){
        print(visited)
        if (from == sink) return flow;
        if (flow == 0) return flow;
        long flow_next = 0;
        long dest;
        for (pll p: destcap[from]){
            dest = p.first;
            if (not visited[dest]){
                path.push_back(&p);
                print(p.first,"pushed")
                visited[dest] = 1;
                flow_next = dfs(min(flow, p.second), dest);
                print(path.size())
                if (flow_next) return flow_next;            
                path.pop_back();
                visited[dest] = 0;
            }
        }
        return flow_next;

    }

    void add_path(){
        long flow = dfs(MAXLONG, source);
        long cur = source;
        pll *p;
        long dest;
        while(not path.empty()){
            p = path.front();

            dest = (*p).first;

            print(cur, dest)
            destcap[cur][dest].second -= flow;
            destcap[dest][cur].second += flow;

            visited[dest] = 0;

            cur = dest;
            path.pop_front();


        }
    }

};


// bool dfs(long i, ml &capto, vl &capsink, ml &matto, ml &matfrom){
//     FOR(j,0,matto[i].size()){
//         if (capto[i][j]){

//         }
//     }
// }


long solve(long t){
    long N;
    cin >> N;


    Maxflow mf = Maxflow(4);

    mf.add_edge(0,1,1);
    mf.add_edge(0,3,1);
    mf.add_edge(2,1,1);
    mf.add_edge_from_source(0,1);
    mf.add_edge_from_source(2,1);
    mf.add_edge_to_sink(1,1);
    mf.add_edge_to_sink(3,1);

    mf.add_path();


    cout << "Case #" << t+1 << ": " << -1 << endl;
    return 0;
}

int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}