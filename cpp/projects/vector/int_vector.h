/**
 * pointer + dynamic storage 
 *
 * */

class IntVector {
public: 
  void push_back(int val); 
  int at(int i);
  int size();
  
private: 
  int allowed = 1; 
  int n = 0; 
  int* buf = new int[allowed]; 
};

