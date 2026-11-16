#include <fstream> 
#include <cmath> 

using namespace std; 

int main() {
  ifstream fin("lostcow.in");
  ofstream fout("lostcow.out"); 
  
  int x, y; 
  fin >> x >> y; 
  
  int sim = x; 
  int prev = x; 
  int step = 1;  
  
  int ans = 0; 
  
  while(true) {
    prev = sim; 
    sim = x + step; 
    
    if(y >= min(prev, sim) && y <= max(prev, sim)) {
      ans += abs(y - prev); 
      break;    
    }
    
    step *= -2;
    ans += abs(sim - prev);
  }

  fout << ans; 
}
