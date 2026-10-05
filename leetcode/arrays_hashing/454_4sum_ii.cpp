#include <vector>
#include <unordered_map> 

using namespace std;

class Solution {
public:
	int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
		int ans = 0, n = nums1.size(); 
		unordered_map<int, int> m; 

		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				int s = nums1[i] + nums2[j]; 
				m[-s]++; 
			}
		}

		for(int k = 0; k < n; k++) {
			for(int l = 0; l < n; l++) {
				int s = nums3[k] + nums4[l]; 
				if (m.contains(s)) ans += m[s]; 
			}
		}
		return ans; 
	}
	
};
