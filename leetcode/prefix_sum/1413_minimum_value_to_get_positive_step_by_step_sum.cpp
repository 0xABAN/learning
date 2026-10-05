#include <vector>
#include <algorithm> 

using namespace std;

class Solution {
public:
	int minStartValue(vector<int>& nums) {
		// find the running sum of nums 
		// keep track of the most negative value we encounter
		// -(that number) + 1 is what we want 

		int s = 0, ans = 0; 
		for(int n : nums) {
			s += n; 
			ans = min(ans, s); 
		}

		return -ans+1; 	
	}
};
