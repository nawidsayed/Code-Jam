#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;


void add_parentheses(vector<char> &vector, long diff){
    if (diff < 0){
        diff = -diff;
        for (long i = 0; i<diff; i++){
            vector.push_back(')');
        }
    }else{
        for (long i = 0; i<diff; i++){
            vector.push_back('(');
        }
    }
}


int main() {
	ios_base::sync_with_stdio(false); 
	long T;
    string s;
    cin >> T;
    
	for(long t = 0; t < T; t++){
		cin >> s;
        vector<char> vector;
        long d, diff;
        char c;
        long nesting = 0;
        for (long i = 0; i<s.size(); i++){
            c = s[i];
            d = c - '0';
            
            diff = d - nesting;
            add_parentheses(vector, diff);
            vector.push_back(c);

            nesting = d;
        }
        add_parentheses(vector, - nesting);

        string out(vector.begin(), vector.end());
    
        cout << "Case #" << t+1 << ": "<< out << endl;        

	}    
}