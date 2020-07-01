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


// TODO how to transfrom string quickly to vector of chars? How to compare strings?
// TODO checkout other containers and see what alogriths there are in algorithm
// TODO checkout cmath
// TODO checkout bitset


int main() {
    ios_base::sync_with_stdio(false); 
    // ================================================================
    // containers and strings
    // ================================================================

    {   
        // Reverse for loop, print works without colon
        FORR(x,0,10){
            // print(x)
        }

        // Initialization and lexiographic sort of matrix 
        ml mat = ml(5, vl(10,0));   
        sort(all(mat));
        print(mat);

        // Initializes a vector and populates with incrementing values starting from offset
        vl vec(10,0);
        iota(all(vec), 3);
        printc(vec);

        // How to create pairs and tuples
        pll p{1,'c'}; // autmatic cast to proper type
        tuple<long, string> t{1, "abc"};
        auto t2 = make_tuple(2,"def", 5); // types are int and const char*
        tuple<long, string, long> t3 = make_tuple(3,"ghi", 10);

        // acessing elements of pair and tuple
        print(p.second)
        print(get<0>(t)) // acces by index 
        print(get<const char*> (t2)) 
        print(get<string> (t3)) // acces by type only works when it's unambiguous

        // Creating and iterating through lists
        list<long> ll{1,2,3,4,5,6};
        for (auto it = next(ll.begin()); it != prev(ll.end()); it++) { // The modifier next and prev are optional
            if (*it == 2) ll.erase(it); // erasing element, still every element is visited once by iterator
            if (*it == 3) ll.insert(it, 12); // inserting element just before current iterator position, 
            if (*it == 4) *it = 22; // replacing element
        }
        printc(ll);

        // Creating and manipulating maps, sets and unordered_maps
        unordered_map<string, long> umap{{"a", 1}}; // similar to map with constant acess time, items are pairs
        umap.insert({"b", 2});
        umap.count("c"); // 1 or 0, use that to check for presence of element, don't use umap["c"]
        umap["d"]; // if not present, will add with default value, even during access time, so be careful.
        for (auto p: umap) print(p.first, p.second);


        // creating and manipulating strings, strings are mutable
        string s = "abcdefghijklmnopqrstuvwxyz";
        print(s.substr(10, 5)) // get subtring by start and length
        s.resize(30, '0'); // cut to first n or fill until n chars
        s.erase(10, 5); // erase section starting from 10 of length 5, opposit of subtr

        print(s)

        string s2 = "***sdf*sdfa*sdf";
        vector<string> vs;

        long index;
        while (true){
            index = s2.find("*");
            if (index < 0){
                vs.push_back(s2);
                break;
            }
            vs.push_back(s2.substr(0, index));
            s2.erase(0, index+1);
        }

        printc(vs);
        

    }

    // ================================================================
    // algorithms
    // ================================================================
    // checkout http://www.cplusplus.com/reference/algorithm/ and https://en.cppreference.com/w/cpp/numeric
    {
        vl vec{1,4,2,3};
        vl vec2{4,2};
        long maxi = MAX(vec); // get maximum of vector
        long argmax = ARGMAX(vec); // get maximum index
        long argmin = min_element(all(vec)) - vec.begin(); // get minimum index, ARGMIN would work too 
        
        string s = "asdfjklasdf"; // algorithm works just fine for strings
        char max_char = *max_element(all(s));
        long argmax_char = ARGMAX(s);
        
        bool all_true = all_of(all(vec), [](long l) {return l>0;}); // similarly any_of, none_of, also works for non-lambda functions

        count(all(s), 'a'); // counts the number of occurances of element in container
        bool equal = vec == vec2; // check for equality of vectors

        long index_begin = search(all(vec), all(vec2)) - vec.begin(); // returns index to first occurence of vec2 in vec
    }


    // ================================================================
    // cmath and numeric
    // ================================================================
    // checkout http://www.cplusplus.com/reference/cmath/ and 
    {
        long power_long = powl(2,10); // power function for integers


    }

    // ================================================================
    // playground and stuff
    // ================================================================

    {
        
    }


}


long gcd(long a, long b){
    // careful, will return negative factors for negative arguments
    if (b == 0) return a;
    return gcd(b, a%b);
}



// Edmond Karp algorithm to solve maxflow
// changes capacity matrix!
// adj contains all children and parents of a node
// cap contains the capacity of all vertex combinations, always non-negative
// s and t denote source and sink identifier
pair<vl, long> bfs(long s, long t, vector<vector<long>> &adj, ml &cap){
    long num_nodes = adj.size();
    vl parents(num_nodes, -1);
    parents[s] = -2; // we don't want to go back to source
    queue<pll> node_flows;
    node_flows.push({s, MAXLONG});

    long cur, flow, next_flow;
    while(!node_flows.empty()){
        cur = node_flows.front().first;
        flow = node_flows.front().second;

        node_flows.pop();

        for (long next: adj[cur]){
            if(parents[next] == -1 && cap[cur][next]){
                parents[next] = cur;
                next_flow = min(flow, cap[cur][next]);
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

// Fenwick tree update and add
// vec represents ft tree and is one longer than arr
// arr contains the raw elements for underlying tree
void update(long i, long v, vl &vec, vl &arr){
    i++;
    long size = vec.size();
    long d = v - arr[i];
    arr[i] = v;
    while (i < size){
        vec[i] += d;
        i += i & -i;
    }
}

long add(long i, vl &vec){ // returns 0 for i = 0;
    long size = vec.size();
    long total = 0;
    while(i > 0){
        total += vec[i];
        i -= i & -i;
    }
    return total;
}

// Kosaraju's algorithm for strongly connected components
// in contains the parents, out contains children for node at respective index
// returns vector with each entry marking the node index of a representative in component
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