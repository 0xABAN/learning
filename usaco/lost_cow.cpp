/*
 *
 * what i learned: y >= min(num1, num2) && y <= max(num1, num2); 
 * when i don't know which of the two is pos / neg 
 *
 * can use two variables, sign and step, to alternate
 * i should revisit this problem
 *
 *
 *
 *
 * */

#include <fstream> 
#include <cmath> 

using namespace std; 

int main() {
  ifstream fin("lostcow.in");
  ofstream fout("lostcow.out");
  
  int x, y; 
  fin >> x >> y; 

  int sim = x; 
  int next = 1; 
  
  int ans = 0; 
  int prev = sim; 
  
  while(true) {
    ans += abs(sim - prev); 
    sim = x + next; 
    
    if(y >= min(prev, sim) && y <= max(prev, sim)) { 
      ans += abs(y - prev); 
      break; 
    } 
     
    next *= -2; 
    
    prev = sim; 
  } 
  
  fout << ans; 
  return 0;
}
