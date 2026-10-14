#include <iostream> 
#include <string>

using namespace std; 

int main() { 
  int n; 
  cin >> n; 

  for(int i = 0; i < n; i++) {
    string word;
    cin >> word; 
    
    int length = word.size(); 
    if (length > 10) {
      cout << word.front() << length-2 << word.back();
    } else {
      cout << word; 
    }
    cout << "\n"; 
  }

  return 0; 
}

