#include <fstream> 
#include <vector>
#include <utility> 
#include <algorithm>

using namespace std; 

int main() {
  ifstream fin("shell.in");
  ofstream fout("shell.out"); 

  int n; 
  fin >> n; 
  
  vector<int> pos{1, 2, 3}; 
  vector<int> cnt{0, 0, 0};
  
  for(int i = 0; i < n; i++) {
    int a, b, g; 
    fin >> a >> b >> g;  
    a--, b--, g--; 

    swap(pos[a], pos[b]);
    cnt[pos[g]]++;  
  }  
  
  int best_score = max({cnt[0], cnt[1], cnt[2]});
  return 0; 
}

