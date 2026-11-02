#include <iostream> 
#include "matrix.h"

using namespace std; 
using namespace linalg; 

int main() {
  Matrix A(5, 5); 
  Matrix B(5, 5);   
  Matrix C = A * B; 
  
  cout << C[2][2];
  
  return 0;  
}
