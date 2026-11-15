#include <fstream>
#include <vector> 
#include <algorithm>

using namespace std; 

int main() {
  ifstream fin("balance.in");
  ofstream fout("balance.out"); 
  
  int n, b; 
  fin >> n >> b; 
  
  vector<int> x(n), y(n); 
  for(int i = 0; i < n; i++) {
    int xi, yi; 
    fin >> xi >> yi; 
    
    x[i] = xi; 
    y[i] = yi; 
  }

  int ans = n; 
  for(const int& xi : x) {
    int a = xi+1; 
    for(const int& yi : y) {
      int b = yi+1; 
  
      int q1 = 0, q2 = 0, q3 = 0, q4 = 0; 
      for(int i = 0; i < n; i++) {
        if(x[i] > a && y[i] > b) {
          q1++;
        }
        else if(x[i] < a && y[i] < b) {
          q2++; 
        }
        else if(x[i] < a && y[i] > b) {
          q3++;  
        }
        else if(x[i] > a && y[i] < b) {
          q4++; 
        }
      }
      
      int curr = max({q1, q2, q3, q4});
      ans = min(ans, curr);
    }
  }

  fout << ans; 
}
