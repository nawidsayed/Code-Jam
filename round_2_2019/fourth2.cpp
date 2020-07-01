#ifndef BZ
#pragma GCC optimize "-O3"
#endif

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

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		eds[i] = {a, b};
		reds[i].clear();
	}
	for (int i = 0; i < n; ++i) {
		for (int j: eds[i])
			reds[j].push_back(i);
	}
	for (int i = 0; i < n; ++i)
		cin >> g[i];
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
		cout << 0 << "\n";
		return;
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
		cout << ans << "\n";
	else
		cout << "UNBOUNDED\n";
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	int tt;
	cin >> tt;
	for (int i = 0; i < tt; ++i) {
		cout << "Case #" << i + 1 << ": ";
		solve();
	}
	return 0;
}


