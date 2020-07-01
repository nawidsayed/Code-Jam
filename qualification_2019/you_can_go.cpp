#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false); 
	long T,n;
	string inp;
	string out;
	char c;
	cin >> T;
	for(long t = 0; t < T; t++){
		cin >> n;
		cin >> inp;
		out = "";
		for(long i = 0; i < inp.length(); i++){
			if(inp[i] == 'E'){
				out.push_back('S');
			}
			else{
				out.push_back('E');
			}
		}
		cout << "Case #" << t+1 << ": " << out << endl;
	}	
}