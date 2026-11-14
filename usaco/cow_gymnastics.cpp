#include <fstream> 
#include <iostream> 
#include <vector> 

using namespace std; 

int main() {
  ifstream fin("gymnastics.in"); 
  ofstream fout("gymnastics.out"); 
  
  int k, n; 
  cin >> k >> n; 
  
  vector<vector<int>> rounds(k, vector<int>(n));
  for(auto& round : rounds) {
    for(int& cow : round) {
      cin >> cow; 
    }
  }
  
  int ans = 0; // # of consistent pairs 
  for(int a = 0; a < n; a++){
    for(int b = 0; b < n; b++) {
      if(a == b) continue; 
      
      bool consistent = true; 
      
      for(int i = 0; i < k; i++) {
        bool found_a = false; 
        bool found_b = false; 
        
        for(int j = 0; j < n; j++) {
          if(rounds[i][j] == a+1) found_a = true; 
          if(rounds[i][j] == b+1) found_b = true; 

          if(found_b && !found_a) consistent = false; 
        }
      }

      if(consistent) ans++; 
    }
  }

  fout << ans;   
}
