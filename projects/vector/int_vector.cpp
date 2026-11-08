#include <string.h>
#include "int_vector.h"

void IntVector::push_back(int val) {
  if(n+1 > cap) {
    cap *= 2; 
    
    int* tmp = new int[cap]; 
    memcpy(tmp, buf, 4*n); 
    
    delete[] buf; 
    buf = tmp;  
  }

  *(buf + n) = val; 
  n++; 
}

int IntVector::at(int i) {
  return *(buf + i); 
}

int IntVector::size() {
  return n; 
} 

