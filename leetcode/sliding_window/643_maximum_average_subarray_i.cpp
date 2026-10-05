#include <vector>
#include <algorithm> 

using namespace std;

class Solution {
public:
	double findMaxAverage(vector<int>& nums, int k) {
		// keep the running sum of the array 
		// it's fixed length, not growing
		// start computing averages once length reaches k 
		
		int s = 0;
		int l = 0; 

		for(int r = 0; r < k; r++) {
			s += nums[r]; 
		}
		
		double ans = (double)s / k; 
		for(int r = k; r < nums.size(); r++) {
			s += nums[r];
			s -= nums[l];
			
			ans = max(ans, (double)s / k); 
			l++; 
		}

		return ans; 
	}
};
