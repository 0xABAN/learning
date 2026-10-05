#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	bool canJump(vector<int>& nums) {
		int allowed = nums[0]; 
		for (int i = 0; i < (int)nums.size(); i++) {
			if (i > allowed) {
				return false; 
			}

			allowed = max(allowed, i+nums[i]);
		}
		return true;  
	}
};
