#include <vector>
#include <iostream> 
using namespace std;

class Solution {
public:
	vector<int> getAverages(vector<int>& nums, int k) {
		int n = nums.size(); 
		int len = 2 * k + 1; 
		vector<int> avgs(n, -1); 
		if (n < len) return avgs; 

		long long s = 0; 
		for (int i = 0; i < len; i++) s += nums[i]; 
		avgs[k] = s / len; 

		for(int i = len; i < n; i++) {
			s = s + nums[i] - nums[i - len]; 
			avgs[i - k] = s / len; 
		}
		
		return avgs; 
	}
};

