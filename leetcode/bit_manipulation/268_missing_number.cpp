#include <vector>

using namespace std;

class Solution {
public:
	int missingNumber(vector<int>& nums) {
		unordered_set<int> s(nums.begin(), nums.end()); 

		for (int i = 0; i <= nums.size(); i++) {
			if (!s.contains(i)) return i; 
		}
		return 0; 
	}
};
