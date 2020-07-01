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

#define print(a) cout << (a) << endl;
#define debug(a) cerr << "cerr: " << (a) << endl;

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

template<typename T, typename S>
void printp(T first, S second){cout << first << " " << second << endl;}

template<typename T> 
void printm(matrix<T> mat){
    for(vector<T> vec: mat){for(T e: vec) cout << e << " "; cout << endl;}
}

template<class Container>
void printc(const Container &cont){
    for (auto e: cont) cout << e << " "; cout << endl;
}

long gcd(long a, long b){
    if (b == 0) return a;
    return gcd(b, a%b);
}

pll search(pll lower, pll upper){
    double eps = 1e-14;
    double u = (1-eps) * upper.first / upper.second;
    double l = (1+eps) * lower.first / lower.second;

    double uc = u;
    double lc = l;

    double ua, la;
    vector<long> rep;
    while (true){
        ua = floor(u);
        u = 1 / (u-ua);
        la = floor(l);
        l = 1 / (l-la);
        if (ua == la){ rep.push_back(ua);}
        else{ rep.push_back(min(ua, la) +1); break;}

    }

    long n = 1;
    long d = 0;
    reverse(all(rep));
    for (long k: rep){
        swap(n,d);
        n += d*k;
    }
    // printp(lc,d);
    // n = long (floor(lc * d + 1));

    return make_pair(n,d);

}


string solver() {
    string fail = "IMPOSSIBLE";
    long c,j,N;
    cin >> N;
    vector<pll> molecules(N);
    FOR(n,0,N){
        cin>>c;
        cin>>j;
        molecules[n] = make_pair(c,j);
    }

    set<pll> ratios;
    pll mol1, mol2;
    long fac;

    vector<pll> larger, smaller;

    FOR(i,0,N){
        mol2 = molecules[i];
        FOR(k,0,i){
            mol1 = molecules[k];

            // print("order")
            // printp(mol1.first, mol1.second);
            // printp(mol2.first, mol2.second);

            j = mol2.first - mol1.first;
            c = mol1.second - mol2.second;

            // printp(c,j);
            
            fac = abs(gcd(c,j));
            c/=fac;
            j/=fac;
            if(c*j == 0){
                if (c-j == 0) return "error";
                if (c-j>0) return fail;
            } 
            else if (c*j < 0) {
                if(j<0) return fail; 
            } else {
                if(c>0){
                    larger.push_back(make_pair(c,j));
                } else {
                    smaller.push_back(make_pair(-c,-j));
                }
            }
        }
    }
    pll biggest, smallest;
    biggest = make_pair(0,1);
    for (auto p: larger){
        if (p.first * biggest.second > p.second * biggest.first) biggest = p;
    }

    smallest = make_pair(1,0);
    for (auto p: smaller){
        if (p.first * smallest.second < p.second * smallest.first) smallest = p;
    }

    // printp(biggest.first, biggest.second);
    // printp(smallest.first, smallest.second);

    if (smallest.first * biggest.second <= smallest.second * biggest.first) return fail;



    pll sol = search(biggest, smallest);

    return to_string(sol.first) + " " + to_string(sol.second);

}



int main(){
    long T;
    cin >> T;

    // IN future write solver so that it returns 0 in case of fail, otherwise it should print sol
    FOR(t,0,T) cout << "Case #" << t+1 << ": " << solver() << endl;
}