#include <fstream> 
#include <vector>
#include <iostream>

using namespace std; 

int main() {
  ifstream fin("shuffle.in");
  ofstream fout("shuffle.out");

  int n; 
  fin >> n; 

  vector<int> final_pos(n);
  for(int& cow : final_pos) fin >> cow; // pos i -> pos j

  vector<int> cow_ids(n); 
  for(int& cow : cow_ids) fin >> cow; 
  
  vector<int> order(n); 

  for(int rounds = 0; rounds < 3; rounds++) {
    for(int i = 0; i < n; i++) {
      int j = final_pos[i]-1; // 
      order[i] = cow_ids[j];
    }
    cow_ids = order;
  }

  for(int& cow : order) fout << cow << "\n"; 
  
  return 0; 
}
