#include <vector> 
#include <utility> 
#include <cstdlib>
#include <stdexcept>


using namespace std; 

class Map {
public: 
  int get(int key);
  void put(int key, int val); 
  void remove(int key); 
  bool contains(int key); 
  int size(); 
private: 
  int slots = 1;
  vector<pair<int, int>>* buf = new vector<pair<int, int>>[slots];  
  int n = 0; 
};
