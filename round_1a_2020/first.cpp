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
void printp(pair<T,S> p){cout << p.first << " " << p.second << endl;}

template<typename T> 
void printm(matrix<T> mat){
    for(vector<T> vec: mat){for(T e: vec) cout << e << " "; cout << endl;}
}

template<class Container>
void printc(const Container &cont){
    for (auto e: cont) cout << e << " "; cout << endl;
}



int main() {
    ios_base::sync_with_stdio(false); 
	long T,N;
    cin >> T;
    for (long t = 0; t<T; t++){
        cin>>N;
        vector<string> vec(N);
        FOR(i,0,N){
            cin >> vec[i];
        }

        string out;

        bool poss = true;
        string s = "*";
        for(string v: vec){
            long pre1 = s.find("*");
            long pre2 = v.find("*");
            long sub = min(pre1, pre2);
            if (s.substr(0, sub) != v.substr(0,sub)){
                poss = false;
                break;
            } else if (pre1 < pre2){
                s.insert(pre1, v.substr(pre1, pre2-pre1));
            }

        }
        if (poss) {
            string s2 = "*";
            for(string v: vec){
                reverse(all(v));
                long pre1 = s2.find("*");
                long pre2 = v.find("*");
                long sub = min(pre1, pre2);
                if (s2.substr(0, sub) != v.substr(0,sub)){
                    poss = false;
                    break;
                } else if (pre1 < pre2){
                    s2.insert(pre1, v.substr(pre1, pre2-pre1));
                }
            }           
            reverse(all(s2));
            if (poss){
                string ss = s + s2;
                long pos = ss.find("*");
                for (string v: vec){
                    long i = v.find("*");
                    long j = v.rfind("*");
                    ss.insert(pos, v.substr(i,j));
                }
                for (char c: ss){
                    if (c != '*') out+=c;
                }
            }            

        }
        if (not poss) out = "*";

        cout << "Case #" << t+1 << ": " << out << endl;

    }
}