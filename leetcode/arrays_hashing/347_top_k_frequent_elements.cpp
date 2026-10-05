#include <vector>
#include <unordered_map> 

using namespace std;

class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> freq; 
		for(int x : nums) freq[x]++;

		vector<vector<int>> buckets(nums.size()+1); // 1 bucket per frequency 
		for(const auto& [num, count] : freq) {
			buckets[count].push_back(num); 
		}
		
		vector<int> ans; 
		for(int i = nums.size(); i > 0; i--) {
			for(int j = 0; j < buckets[i].size(); j++) {
				ans.push_back(buckets[i][j]);

				if (ans.size() == k) {
					return ans; 
				}
			}
		}

		return ans; 
	}
};
