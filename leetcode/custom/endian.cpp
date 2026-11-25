#include <cstdint>
#include <vector> 
#include <iostream> 

using namespace std; 

vector<uint8_t> encode(uint32_t num, bool little_endian) {
  vector<uint8_t> bytes(4, 0); 
   
  for(size_t i = 0; i < bytes.size(); i++){
    uint8_t b = num % 256; 
    num /= 256; 
     
    size_t j = little_endian ? i : bytes.size()-i-1; 
    bytes[j] = b; 
  }

  return bytes;
}

uint32_t decode(const vector<uint8_t>& bytes, bool little_endian) {
  uint32_t ans = 0;
  uint32_t place = 1; 

  for(size_t i = 0; i < bytes.size(); i++) {
    size_t j = little_endian ? i : bytes.size()-i-1; 
    ans += bytes[j] * place;
    place *= 256; 
  }
  
  return ans; 
}

int main() {
  return 0; 
}
