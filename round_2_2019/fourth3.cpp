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


vl mass;
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

    if (loop[n]>0 && mass[n]) throw 1;

    for (long c: out[n]){
        mass[c] = (mass[c] + mass[n]) % mod;
    }
    mass[n] = 0;
}

long solve(vl as, vl bs, vl ms){
    long M = ms.size();
    vector<vl> in(M);
    vector<vl> out(M);
    mass = vl(M);
    

    long l,r;
    FOR(m,0,M){
        l = as[m];
        r = bs[m];
        l--, r--;
        in[l].push_back(m);
        in[r].push_back(m);
        out[m] = vl({l,r});
    }

    FOR(m,0,M) mass[m] = ms[m];

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

    vl visited(M);
    // for (auto s: ins) printc(s);
    
    // print(mass)

    // print(who)
    // print(loop)


    try{
        for (long p: ins[0]){
            back(p, ins, outs, visited, loop);    
        }
    }
    catch (int param){
        return -1;
    }

    if (mass[0] > 0 && loop[0] > 1){
        return -1;        
    }
    // print(who)
    // print(mass)
    
    return mass[0];
}



#define ALL(v) (v).begin(), (v).end()
#define rep(i, l, r) for (int i = (l); i < (r); ++i)

using ll = long long;
using ld = long double;
using ull = unsigned long long;

using namespace std;


/*
ll pw(ll a, ll b) {
	ll ans = 1; while (b) {
		while (!(b & 1)) b >>= 1, a = (a * a) % MOD;
		ans = (ans * a) % MOD, --b;
	} return ans;
}
*/

const int N = 1e5 + 100;

int n;
vector<int> eds[N];
vector<int> reds[N];

ll g[N];

int fl[N];
int en[N];

void dfs1(int v) {
	fl[v] = 1;
	for (int u: reds[v])
		if (!fl[u])
			dfs1(u);
}

void dfs2(int v) {
	fl[v] = 1;
	for (int u: eds[v])
		if (!fl[u])
			dfs2(u);
}

int p[N];

const ll MOD = 1e9 + 7;

int get(int x) {
	if (p[x] == x)
		return x;
	return p[x] = get(p[x]);
}

int was[N];
ll dp[N];
int gfl;

void dfs3(int v) {
	was[v] = 1;
	if (eds[v].size() == 1) {
		dp[v] = 1;
		was[v] = 2;
		return;
	}
	dp[v] = 0;
	for (int u: eds[v]) {
		int x = get(u);
		if (was[x] == 1)
			gfl = 1;
		else if (was[x] == 2)
			dp[v] = (dp[v] + dp[x]) % MOD;
		else {
			dfs3(x);
			dp[v] = (dp[v] + dp[x]) % MOD;
		}
	}
	was[v] = 2;
}

long solve2(vl as, vl bs, vl ms) {
    n = ms.size();
	for (int i = 0; i < n; ++i) {
		int a, b;
		a = as[i];
        b = bs[i];
		--a, --b;
		eds[i] = {a, b};
		reds[i].clear();
	}
	for (int i = 0; i < n; ++i) {
		for (int j: eds[i])
			reds[j].push_back(i);
	}
	for (int i = 0; i < n; ++i)
		g[i] = ms[i];
	for (int i = 0; i < n; ++i)
		fl[i] = 0;
	for (int i = 0; i < n; ++i)
		en[i] = 1;
	dfs1(0);
	for (int i = 0; i < n; ++i)
		en[i] &= fl[i];
	for (int i = 0; i < n; ++i)
		fl[i] = 0;
	for (int i = 0; i < n; ++i)
		if (g[i] && !fl[i])
			dfs2(i);
	for (int i = 0; i < n; ++i)
		en[i] &= fl[i];
	if (en[0] == 0) {
		return 0;
	}
	for (int i = 0; i < n; ++i) {
		p[i] = i;
	}
	for (int i = 0; i < n; ++i) {
		if (en[i]) {
			vector<int> tmp;
			for (int j: eds[i])
				if (en[j])
					tmp.push_back(j);
			eds[i] = tmp;
		}
	}
	if (eds[0].empty())
		eds[0] = {0};
	for (int i = 0; i < n; ++i) {
		if (en[i]) {
			if (eds[i].size() == 1) {
				int x = get(eds[i][0]);
				if (x == i)
					continue;
				p[i] = x;
				g[x] = (g[x] + g[i]) % MOD;
				en[i] = 0;
			}
		}
	}
	for (int i = 0; i < n; ++i)
		was[i] = 0;
	gfl = 0;
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		if (en[i]) {
			if (!was[i])
				dfs3(i);
			ans = (ans + dp[i] * g[i]) % MOD;
		}
	}
	if (!gfl)
		return ans;
	else
        return -1;
}


int main(){
    long M = 100;
    long ans, ans2;
    FOR(t,0,1000){
        vl as, bs, ms;
        long r1,r2;
        FOR(m,0,M){
            r1 = rand() % M;
            r2 = (r1 + 1 + rand() % (M-1)) % M;

            as.push_back(r1+1);
            bs.push_back(r2+1);
            ms.push_back(m+1);
        }
        ans = solve(as,bs,ms);
        ans2 = solve2(as,bs,ms);
        if(ans != ans2){
            print(as)
            print(bs)
            print(ms)
            print(ans, ans2)
        }
    }
}