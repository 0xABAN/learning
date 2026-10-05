#include <vector> 
#include <utility>
using namespace std;

class Solution { 
public: 
	void moveZeroes(vector<int>& nums) {
		// keep track of leftmost zero, swap with first occurrence of nonzero 
		// {0, 1, 0, 3, 12}
		// {1, 0, 0, 3, 12}
		
		int i = 0;  
		int j = 0; 

		while (i < nums.size()-1 && j < nums.size()-1) {
			if (nums[i] != 0) { 
				i++; 
				j = i; 
				continue; 
			}

			j++; 
			if (nums[j] != 0) { 
				std::swap(nums[i], nums[j]); 
			} 
		}
	}
}; 
