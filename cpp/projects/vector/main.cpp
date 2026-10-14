#include <iostream>

#include "int_vector.h"

int main() {
  IntVector v; 
  v.push_back(5); 
  v.push_back(10);  
  
  std::cout << v.at(0) << "\n"; 
  std::cout << v.size();  
  
  return 0; 
}
