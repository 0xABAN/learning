#include <vector>
#include <unordered_map>
#include <algorithm> 

using namespace std;

class Solution {
public:
	int findShortestSubArray(vector<int>& nums) {
		unordered_map<int, vector<int>> stats;
		int degree = 0, n = nums.size();

		for (int i = 0; i < n; i++) {
			auto& value = stats[nums[i]];
			if (value.empty()) value = {i, i, 0}; // first, last, count

			value[1] = i;
			degree = max(degree, ++value[2]);
		}

		int answer = n;
		for (const auto& [number, value] : stats) {
			if (value[2] == degree) {
				answer = min(answer, value[1] - value[0] + 1);
			}
		}

		return answer;
	}
};

