#include <iostream> 
#include <cmath>
#include <vector> 
#include <algorithm> 

using namespace std; 

int main() {
  int n; 
  cin >> n; 
  
  vector<int> x(n); 
  for(int& xi : x) cin >> xi;  

  vector<int> y(n); 
  for(int& yi : y) cin >> yi; 

  int ans = 0; 
  for(int i = 0; i < n; i++) {
    for(int j = i+1; j < n; j++) {
      int dx = x[i] - x[j]; 
      int dy = y[i] - y[j]; 

      int sq = dx*dx + dy*dy; 
      ans = max(ans, sq);
    }
  }
  cout << ans; 
}
