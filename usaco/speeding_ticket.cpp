#include <fstream> 
#include <vector> 
#include <algorithm>

using namespace std; 

struct Segment {
  int len, limit;  
};

int main() {
  ifstream fin("speeding.in");
  ofstream fout("speeding.out");

  int n, m;
  fin >> n >> m; 
  
  vector<Segment> road(n); 
  int prev_seg = 0; 
  for(int i = 0; i < n; i++) {
    int len, limit; 
    fin >> len >> limit; 

    road[i].len = len + prev_seg; 
    road[i].limit = limit; 
    prev_seg += len;  
  }

  vector<Segment> bessie(m); 
  prev_seg = 0; 
  for(int i = 0; i < m; i++) {
    int len, limit; 
    fin >> len >> limit; 

    bessie[i].len = len + prev_seg; 
    bessie[i].limit = limit; 
    prev_seg += len;  
  }
  
  int ans = 0;
  int i = 0, j = 0; 
  
  while (i < m && j < n) {
    int diff = max(0, bessie[i].limit - road[j].limit); 
    ans = max(ans, diff);

    if(bessie[i].len < road[j].len) {
      i++;
    } else if(bessie[i].len > road[j].len) {
      j++; 
    } else {
      i++;
      j++;
    }

  }

  fout << ans; 
}
