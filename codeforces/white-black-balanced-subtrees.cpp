#include <vector>
#include <unordered_map>
#include <iostream> 

using namespace std; 

int dfs(int node, int& count, unordered_map<int, vector<int>>& g, vector<char>& colors) { 
  int freq = 0; 
  for(int child : g[node]) {
    freq += dfs(child, count, g, colors); 
  }
  
  freq += (colors[node-1] == 'W') ? 1 : -1;  
  if(freq == 0) count++; 
  
  return freq;  
} 

void solve() { 
  int n; 
  cin >> n; 

  unordered_map<int, vector<int>> g;
  for(int i = 2, x; i <= n; i++) { 
    cin >> x; 
    g[x].push_back(i);
  } 

  vector<char> colors(n); 
  for(char& x : colors) { 
    cin >> x; 
  }
  
  int ans = 0;   
  dfs(1, ans, g, colors);
  cout << ans << '\n'; 
}

int main() {
  int t; 
  cin >> t; 
  
  while(t > 0) { 
    t--; 
    solve(); 
  }  
}
