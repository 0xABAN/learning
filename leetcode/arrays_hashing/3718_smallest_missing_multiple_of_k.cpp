#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
	int missingMultiple(vector<int>& nums, int k) {
		unordered_set<int> s(nums.begin(), nums.end());
		int c = 1;

		while (true) {
			if (!s.contains(c * k)) {
				return c * k;
			}
			c++;
		}
		return 0;
	}
};
