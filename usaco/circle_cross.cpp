#include <fstream>
#include <vector> 
#include <unordered_map>

using namespace std;

int main() {
  ifstream fin("circlecross.in"); 
  ofstream fout("circlecross.out"); 
  
  int n = 52; 
  vector<char> s(n); // # of cow start + end locs
  for(char& c : s) fin >> c; 
  
  int ans = 0; 
  unordered_map<char, int> seen; 
     
  for(int i = 0; i < n; i++) {
    char c = s[i]; 
   
    if(seen.contains(c)) {
      int start_idx = seen[c]+1; 
      
      for(int j = start_idx; j < i; j++) {
        if(seen.contains(s[j])) ans++; 
      }  
      
      seen.erase(c); 
    } else {
      seen[c] = i; 
    }
  }
  
  fout << ans; 
}
