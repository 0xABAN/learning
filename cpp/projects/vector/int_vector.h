class IntVector {
public: 
  void push_back(int val); 
  int at(int i); 
  int size(); 
  
  ~IntVector() { delete[] buf; }
private: 
  int n = 0; 
  int cap = 1; 
  int* buf = new int[cap]; 
}; 
