#include <vector>

using namespace std;

class Solution {
public:
	void reverseString(vector<char>& s) {
		char* lp = &s.front(); 
		char* rp = &s.back();

		while (lp < rp) {
			swap(lp, rp)

			lp++; 
			rp--; 
		}
	}
};

