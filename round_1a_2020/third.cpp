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

template<typename T> 
void printm(matrix<T> mat){
    for(vector<T> vec: mat){for(T e: vec) cout << e << " "; cout << endl;}
}

template<class Container>
void printc(const Container &cont){
    for (auto e: cont) cout << e << " "; cout << endl;
}

typedef tuple<long,long,long,long,long> dancer;
typedef pair<long,long> coord;

long calc_score(list<coord> &l, vector<vector<dancer>> &mat){
    dancer d;
    long sum = 0;
    for(coord e: l){
        d = mat[e.first][e.second];
        sum += get<0>(d);}
    return sum;
}

void update(list<coord> &ll, vector<vector<dancer>> &mat){
    long r, c;
    long row, col;
    dancer d;

    for(coord co: ll){
        r = co.first;
        c = co.second;
        d = mat[r][c];

        row = get<1>(d);
        if (row != -1) get<2>(mat[row][c]) = get<2>(d);

        row = get<2>(d);
        if (row != -1) get<1>(mat[row][c]) = get<1>(d);

        col = get<3>(d);
        if (col != -1) get<4>(mat[r][col]) = get<4>(d);

        col = get<4>(d);
        if (col != -1) get<3>(mat[r][col]) = get<3>(d);

        
    }
}

bool pass(coord co, vector<vector<dancer>> &mat){

    long countNeigh = 0;
    long sumNeigh = 0;
    long r,c;
    long row, col;

    r = co.first;
    c = co.second;
    dancer d = mat[r][c];

    row = get<1>(d);
    if (row != -1) {countNeigh++; sumNeigh += get<0>(mat[row][c]);}

    row = get<2>(d);
    if (row != -1) {countNeigh++; sumNeigh += get<0>(mat[row][c]);}

    col = get<3>(d);    
    if (col != -1) {countNeigh++; sumNeigh += get<0>(mat[r][col]);}

    col = get<4>(d);
    if (col != -1) {countNeigh++; sumNeigh += get<0>(mat[r][col]);}

    return get<0>(d) * countNeigh >= sumNeigh;
}

int main() {
    long T,R,C;
    cin >> T;
    FOR(t,0,T){
        cin >> R;
        cin >> C;
        long skill;

        vector<vector<dancer>> mat(R, vector<dancer>(C));
        list<coord> l;

        FOR(r,0,R){
            FOR(c,0,C){
                cin >> skill;
                dancer d{skill, r-1, r+1, c-1, c+1};
                if (r == R-1) get<2>(d) = -1;
                if (c == C-1) get<4>(d) = -1;
                mat[r][c] = d;
                l.push_back(make_pair(r,c));
            }
        }

        long cur = -1;
        long next;
        long total = 0;

        while (true) {
            next = calc_score(l, mat);
            if (next == cur){
                break;
            } else {
                cur = next;
                total += cur;

                list<coord> ll;
                for (list<coord>::iterator it = l.begin(); it != l.end(); it++){
                    coord co = *it;
                    if (not pass(co, mat)){
                        ll.push_back(co);
                        l.erase(it++);
                        it--;
                        
                    }
                }
                update(ll, mat);
            }
        }

        cout << "Case #" << t+1 << ": " << total << endl;
    }
}