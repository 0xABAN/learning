#include <vector>

using namespace std;

class Solution {
public:
	void reverse(int* begin, int* end) {
		int* lp = begin; 
		int* rp = end-1; 
		int temp; 

		while (lp < rp) {
			temp = *lp; 
			*lp = *rp; 
			*rp = temp; 

			++lp; 
			--rp; 
		}	
	}

	void rotate(vector<int>& nums, int k) {
		int s = k % nums.size(); 

		reverse(nums.data(), nums.data()+nums.size()); 
		reverse(nums.data(), nums.data()+s);
		reverse(nums.data()+s, nums.data()+nums.size()); 

	}
};
