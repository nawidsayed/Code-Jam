#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

string getLastLetters(string s, long k){
    return s.substr(s.size()-k, k);
}

int main() {
    ios_base::sync_with_stdio(false); 
	long T,N;
    long W = 50;
    string s;
    cin >> T;
	for(long t = 0; t < T; t++){
        cin >> N;
        vector<string> words;
        for (long n = 0; n<N; n++){
            cin >> s;
            reverse(s.begin(), s.end());
            words.push_back(s);
        }

        sort(words.begin(), words.end());

        

        long sum = 0;

        string word, word_previous;

        for (long w = W; w >= 1; w--){

            // for (string word : words) cout << w << " " << word << endl;

            set<string> suffix_used;
            vector<string> words_available;

            words.push_back("1");

            for (long i = 1; i < words.size(); i++){
                word_previous = words[i-1];
                word = words[i];

                long length_min = min(word_previous.size(), word.size());
                
                long length_identical = 0;
                for (long i = 0; i < length_min; i++){
                    if (word[i] == word_previous[i]) length_identical ++;
                    else break;
                }

                if (length_identical >= w){
                    string suffix = word.substr(0, w);
                    if (suffix_used.count(suffix) == 0){
                        suffix_used.insert(suffix);
                        sum += 2;
                        i++;
                    } else {
                        words_available.push_back(word_previous);
                    }                  
                } else {
                    words_available.push_back(word_previous);
                }

            }

            words = words_available;
        }
        cout << "Case #" << t+1 << ": "<< sum << endl;    

    }
}