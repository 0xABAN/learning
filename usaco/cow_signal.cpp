#include <fstream> 
#include <vector> 

using namespace std; 

int main() {
  ifstream fin("cowsignal.in");
  ofstream fout("cowsignal.out");

  int m, n, t; 
  fin >> m >> n >> t; 
  
  auto input = vector<vector<char>>(m, vector<char>(n));
  for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++) {
      char c; 
      fin >> c; 
      
      input[i][j] = c; 
    }
  }

  for(int i = 0; i < m; i++) {
    for(int l = 0; l < t; l++) { 
      for(int j = 0; j < n; j++) { 
        char c = input[i][j];
        for(int k = 0; k < t; k++) { 
          fout << c;
        }
      }
      fout << '\n'; 
    }
  }
}
