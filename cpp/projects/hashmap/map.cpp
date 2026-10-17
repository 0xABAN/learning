#include "map.h"


void Map::put(int key, int val) {
  int bucket = abs(key % slots);
  for(int i = 0; i < buf[bucket].size(); i++){
    auto [k, v] = buf[bucket][i]; 
    if (k == key) {
      buf[bucket][i] = {key, val}; 
      return;
    }
  }

  if (n + 1 > slots) {
    int old_slots = slots; 
    slots *= 2; 
  
    vector<pair<int, int>>* temp_buf = new vector<pair<int, int>>[slots];   
    for(int i = 0; i < old_slots; i++) {
      for(int j = 0; j < buf[i].size(); j++) {
        auto [k, v] = buf[i][j];
        
        temp_buf[abs(k % slots)].push_back({k, v});
      }
    }
    
    delete[] buf;
    buf = temp_buf; 
  }
  
  buf[abs(key % slots)].push_back({key, val});
  n++;  
}

int Map::size() {
  return n; 
}

bool Map::contains(int key) {
  int bucket = abs(key % slots); 
  for(int i = 0; i < buf[bucket].size(); i++) {
    auto [k, v] = buf[bucket][i]; 
    if(k == key) return true; 
  }
  return false;
}

int Map::get(int key) {
  int bucket = abs(key % slots); 
  for(int i = 0; i < buf[bucket].size(); i++) {
    auto [k, v] = buf[bucket][i]; 
    if(k == key) return v; 
  }

  throw out_of_range("not found, u mad");
}

void Map::remove(int key) {
  int bucket = abs(key % slots); 
  auto& vec = buf[bucket];

  for(int i = 0; i < vec.size(); i++) {
    auto [k, v] = vec[i]; 

    if (k == key) {
      n--; 
      vec.erase(vec.begin() + i);
      return;
    }    
  }
}
