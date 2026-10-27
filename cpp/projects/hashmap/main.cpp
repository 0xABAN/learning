#include <iostream>  
#include "map.h"

int main() {
  Map a;
  
  a.put(1, 2); 
  a.put(2, 3); 
  a.put(3, 4); 
  
  Map b = a; 
  b.put(5, 6); 

  std::cout << a.contains(5); 

  
  return 0;  
}
