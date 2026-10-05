#include <vector>

using namespace std;

class Solution {
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		// smallest length of sub where s > target 
		// maintain running sum. when subarray > target, decrease from left 
		// [1,4,4]

		int ans = nums.size()+1; 
		int s = 0; 
		int l = 0; 


		for (int r = 0; r < nums.size(); r++) {
			s += nums[r]; // 5
			
			while (l < nums.size() && s-nums[l] >= target) { 
				s -= nums[l]; // 1
				l++; // 1
			}
			
			// s = 4
			if (s >= target) { // yes 
				ans = min(ans, r-l+1); // 4
			}
		}

		if (ans == nums.size()+1) {
			return 0; 
		} else { 
			return ans; 
		}
	}
};



