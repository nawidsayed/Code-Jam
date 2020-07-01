#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
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
            // reverse(s.begin(), s.end);
            words.push_back(s);
        }

        long sum = 0;
        






        vector<string> words_before;
        for (long w = 50; w > 0; w--){
            vector<string> words_current;
            for (string word: words_before){
                words_current.push_back(getLastLetters(word, w));
            }
            for (string word: words){
                if (word.size() == w) {
                    words_current.push_back(word);
                }
            }
            sort(words_current.begin(), words_current.end());

            for (string word: words_current){
                // cout << word << endl;
            }

            string word_previous = "-1";
            long counter = 1;

            vector<string> words_next;

            words_current.push_back("dummy-2");

            for (string word: words_current){
                if (word == word_previous) {
                    counter += 1;
                    if (counter == 1) {
                        sum += 2;
                    } 
                    if (counter >= 2) {
                        words_next.push_back(word_previous);
                    }
                } else {
                    if (counter == 0){
                        words_next.push_back(word_previous);
                    }
                    if (counter >= 2){
                        words_next.push_back(word_previous);
                    }
                    counter = 0;
                }
                word_previous = word;
            }


            words_before = words_next;
        }

        cout << "Case #" << t+1 << ": "<< sum << endl;    

    }
}