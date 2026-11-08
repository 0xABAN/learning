#include <vector> 
#include <utility> 
#include <cstdlib>
#include <stdexcept>

using std::vector, std::pair, std::out_of_range; 

class Map {
private: 
  int slots = 1;
  int n = 0; 
  vector<pair<int, int>>* buf = new vector<pair<int, int>>[slots];  
  
public: 
  Map() {} 
  
  Map(const Map& m) : 
    slots(m.slots), 
    n(m.n), 
    buf(new vector<pair<int, int>>[m.slots])
  {

    for(int bucket = 0; bucket < slots; bucket++) {
      buf[bucket] = m.buf[bucket]; 
    }
  }
  
  int get(int key);
  void put(int key, int val); 
  void remove(int key); 
  bool contains(int key); 
  int size(); 

  ~Map() { delete[] buf; } 
};
