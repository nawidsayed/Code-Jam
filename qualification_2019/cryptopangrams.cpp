#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <deque>
#include <list>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false); 
	long T,n,l, prod, p, pl;
	deque<long> v;
	set<long> primes;
	map<long, char> dict;
	string out;
	cin >> T;
	for(long t = 0; t < T; t++){
		out = "";
		primes = {};
		dict = {};
		v = {};
		cin >> n;
		cin >> l;
		cin >> prod;
		for(long p = 2; p <= n; p++){
			if(prod % p == 0){
				pl = prod / p;
				v.push_back(p);
				v.push_back(pl);
				break;
			}
		}
		for(long i = 1; i < l; i++){
			cin >> prod;
			pl = v.back();
			if(prod % pl != 0){
				pl = v[v.size()-2];
				v.pop_front();
				v.push_back(pl);
			}


			p = prod / pl;
			v.push_back(p);
		}
		for (long i = 0; i < v.size(); i++){
			primes.insert(v[i]);
		}
		long index = 65;
		for(long p : primes){
			dict.insert(pair<long,char>(p, (char) index));
			index++;
		}
		for(long p : v){
			out.push_back(dict[p]);
		}
		cout << "Case #" << t+1 << ": " << out << endl;
	}	
}