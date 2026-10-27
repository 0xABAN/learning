#include <iostream>
#include "int_vector.h" 


int main() {
  IntVector v; 
  
  for(int i = 0; i < 20; i++) {
    v.push_back(i); 

    std::cout << "size: " << v.size() << ", val: " << v.at(i) << "\n"; 
  }
  
  return 0; 
}
