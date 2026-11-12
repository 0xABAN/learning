#include <fstream> 
#include <vector> 
#include <algorithm> 

using namespace std; 

int main() {
  ifstream fin("blist.in");
  ofstream fout("blist.out");

  int n; 
  fin >> n; 
  
  int ans = 0;
  vector<int> time(1'000, 0); 
  
  for(int i = 0; i < n; i++) {
    int start; int end; int buckets; 
    fin >> start >> end >> buckets; 
    
    for(; start < end; start++) {
      time[start] += buckets;  
      ans = max(ans, time[start]);
    }
  }
  fout << ans;  
  
  return 0; 
}
