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



pair<vl, long> bfs(long s, long t, vector<vector<long>> &adjacent, ml &capacity){
    long num_nodes = adjacent.size();
    vl parents(num_nodes, -1);
    parents[s] = -2; // we don't want to go back to source
    queue<pll> node_flows;
    node_flows.push({s, MAXLONG});

    long cur, flow, next_flow;
    while(!node_flows.empty()){
        cur = node_flows.front().first;
        flow = node_flows.front().second;

        node_flows.pop();

        for (long next: adjacent[cur]){
            if(parents[next] == -1 && capacity[cur][next]){
                parents[next] = cur;
                next_flow = min(flow, capacity[cur][next]);
                node_flows.push({next, next_flow});
                if (next == t) {
                    return make_pair(parents, next_flow);
                }
            }
        }
    }
    return make_pair(parents, 0L);
}

long maxflow(long s, long t, vector<vector<long>> &adjacent, ml &capacity){
    long total_flow = 0;

    long prev, cur;

    while(true){
        pair<vl, long> search = bfs(s,t,adjacent,capacity);
        vl parents = search.first;
        long flow = search.second;
        if (!flow) return total_flow;
        total_flow += flow;
        cur = t;
        while(cur != s){
            prev = parents[cur];
            capacity[prev][cur] -= flow;
            capacity[cur][prev] += flow;
            cur = prev;
        }
    }
}

long R,C;
matrix<char> mat;

bool propagateU(long r, long c, list<pll> &cells);
bool propagateD(long r, long c, list<pll> &cells);
bool propagateL(long r, long c, list<pll> &cells);
bool propagateR(long r, long c, list<pll> &cells);

bool propagateU(long r, long c, list<pll> &cells){
    r--;
    if (r == -1) return true;
    if (mat[r][c] == '#') return true;
    if (mat[r][c] == '-' || mat[r][c] == '|') return false;

    if (mat[r][c] == '.') {
        cells.push_back({r,c});
        return propagateU(r, c, cells);
    }
    if (mat[r][c] == '/') return propagateR(r,c, cells);
    if (mat[r][c] == '\\') return propagateL(r,c, cells);
    return false;
}

bool propagateD(long r, long c, list<pll> &cells){
    r++;
    if (r == R) return true;
    if (mat[r][c] == '#') return true;
    if (mat[r][c] == '-' || mat[r][c] == '|') return false;

    if (mat[r][c] == '.') {
        cells.push_back({r,c});
        return propagateD(r, c, cells);
    }
    if (mat[r][c] == '/') return propagateL(r,c, cells);
    if (mat[r][c] == '\\') return propagateR(r,c, cells);
    return false;
}

bool propagateL(long r, long c, list<pll> &cells){
    c--;
    if (c == -1) return true;
    if (mat[r][c] == '#') return true;
    if (mat[r][c] == '-' || mat[r][c] == '|') return false;

    if (mat[r][c] == '.') {
        cells.push_back({r,c});
        return propagateL(r, c, cells);
    }
    if (mat[r][c] == '/') return propagateD(r,c, cells);
    if (mat[r][c] == '\\') return propagateU(r,c, cells);
    return false;
}

bool propagateR(long r, long c, list<pll> &cells){
    c++;
    if (c == C) return true;
    if (mat[r][c] == '#') return true;
    if (mat[r][c] == '-' || mat[r][c] == '|') return false;

    if (mat[r][c] == '.') {
        cells.push_back({r,c});
        return propagateR(r, c, cells);
    }
    if (mat[r][c] == '/') return propagateU(r,c, cells);
    if (mat[r][c] == '\\') return propagateD(r,c, cells);
    return false;
}

long solve(long t){
    cin >> R >> C;
    mat = matrix<char>(R, vector<char>(C,'.'));
    vector<pll> lasers;
    long nodeId = 0;
    ml nodeLookup(R,vl(C));
    set<long> firstLaser;
    char ch;
    FOR(r,0,R){
        FOR(c,0,C){
            cin >> ch;
            mat[r][c] = ch;
            if (ch == '|' || ch == '-'){
                lasers.push_back(make_pair(r,c));
                nodeLookup[r][c] = nodeId;
                firstLaser.insert(nodeId);
                nodeId++;
                nodeId++;
            }
            if (ch == '.') {
                nodeLookup[r][c] = nodeId;
                nodeId++;
            }
        }
    }


    ml matSeen = ml(R, vl(C,0));
    vector<pair<long, list<pll>>> mapping;

    map<pll, char> positions;
    set<pll> rotLasers;

    for (pll laser: lasers){
        long r = laser.first;
        long c = laser.second;
        list<pll> cellsH, cellsV;
        bool h = propagateL(r,c,cellsH) && propagateR(r,c,cellsH);
        bool v = propagateU(r,c,cellsV) && propagateD(r,c,cellsV);
        if (!h && !v){
            cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
            return 0;
        } 
        if (h && v){
            long laserId = nodeLookup[r][c];
            mapping.push_back({laserId, cellsH});
            mapping.push_back({laserId+1, cellsV});
            rotLasers.insert(laser);
        }
        else if (h){
            for (pll cell: cellsH) matSeen[cell.first][cell.second] = 1;
            positions[laser] = '-';
        }
        else if (v){
            for (pll cell: cellsV) matSeen[cell.first][cell.second] = 1;
            positions[laser] = '|';
        }
    }

    if (mapping.size() == 0) {
        FOR(r,0,R){
            FOR(c,0,C){
                if (mat[r][c] == '.' && !matSeen[r][c]){
                    cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
                    return 0;  
                }
            }
        }
        pll laser;
        for (auto p: positions){
            laser = p.first;
            mat[laser.first][laser.second] = p.second;
        }
        cout << "Case #" << t+1 << ": " << "POSSIBLE" << endl;
        FOR(r,0,R){
            FOR(c,0,C){
                cout << mat[r][c];
            }
            cout << endl;
        }        
        return 0;  
    }

    vector<vector<long>> adj(nodeId + 2);
    ml cap(nodeId + 2, vl(nodeId + 2));

    long s = nodeId;
    long s2 = nodeId+1;

    long prev = -2;

    set<pll> emptyCells;

    for (pair<long, list<pll>> mapp: mapping){
        for(pll p: mapp.second) {
            if (! matSeen[p.first][p.second])emptyCells.insert(p);
        }
    }

    for (pair<long, list<pll>> mapp: mapping){
        long laserId = mapp.first;
        print(laserId)
        auto l = mapp.second;

        if (firstLaser.count(laserId)){
            adj[laserId].push_back(laserId+1);
            adj[laserId+1].push_back(laserId);
            cap[laserId][laserId+1] = 1;

            adj[s].push_back(laserId);
            adj[laserId].push_back(s);
            cap[s][laserId] = 1;
        }
        


        prev = laserId;

        for (pll e: l){
            long cellId = nodeLookup[e.first][e.second];
            if (matSeen[e.first][e.second]<=0){
                adj[laserId].push_back(cellId);
                adj[cellId].push_back(laserId);
                cap[laserId][cellId] = 1;
                if (matSeen[e.first][e.second] == 0){
                    adj[cellId].push_back(s2);
                    adj[s2].push_back(cellId);
                    cap[cellId][s2] = 1;
                }
                matSeen[e.first][e.second] =-1;
            }
        }
    }

    print(s,s2)
    print(adj)
    print(cap)
    

    long flow = maxflow(s, s2, adj, cap);

    print(flow)

    if (flow != emptyCells.size()){
        cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
        return 0;
    }

    for (pll laser: rotLasers){
        long laserId = nodeLookup[laser.first][laser.second];
        if(cap[laserId][laserId]){
            positions[laser] = '|';
        }
        else {
            positions[laser] = '-';
        }
    }

    for (auto p: positions){
        pll laser = p.first;
        mat[laser.first][laser.second] = p.second;
    }    
    
    cout << "Case #" << t+1 << ": " << "POSSIBLE" << endl;
    FOR(r,0,R){
        FOR(c,0,C){
            cout << mat[r][c];
        }
        cout << endl;
    }        
    return 0;  


}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}