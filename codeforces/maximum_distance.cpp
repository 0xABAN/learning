#include <iostream> 
#include <cmath>
#include <vector> 
#include <algorithm> 

using namespace std; 

int squared_euclidean(int x1, int y1, int x2, int y2) {
  int a = pow(x1 - x2, 2.0);
  int b = pow(y1 - y2, 2.0); 
  return a + b; 
}

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
      ans = max(ans, squared_euclidean(x[i], y[i], x[j], y[j]));
    }
  }
  cout << ans; 
}
