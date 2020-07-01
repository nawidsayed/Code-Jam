#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// Senate task

char translate(int i){
  char s = char(i+65);
  return s;  
}

int num_parties(int* arr, int n){
  int nonzeros = 0;
  for(int i = 0; i < n; i++){
    if(arr[i] != 0){
      nonzeros++;
    }
  }
  return nonzeros;
}

int max_party(int* arr, int n){
  int max = -1;
  int argmax = -1;
  for(int i = 0; i < n; i++){
    if(arr[i] > max){
      max = arr[i];
      argmax = i;
    }
  }
  return argmax;
}

int main() {
  int t, n;
  cin >> t;
  for(int i = 0; i < t; i++){
    cin >> n;
    int arr[n];
    for(int j = 0; j < n; j++){
      cin >> arr[j];
    }
    cout << "Case #" << i+1 << ":";
    while(true){
      if(num_parties(arr,n) > 2){
        int remove = max_party(arr,n);
        arr[remove] -= 1;
        cout << " " << translate(remove);
      } 
      else if(num_parties(arr,n) == 2){
        int remove[2];
        for(int k=0; k<2; k++){
          remove[k] = max_party(arr,n);
          arr[remove[k]] -= 1;
        }
        cout << " " << translate(remove[0]) << translate(remove[1]);
      }
      else{
        cout << endl;
        break;
      }
    }
  }
}

