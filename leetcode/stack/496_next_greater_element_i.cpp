#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
		vector<int> ans(nums1.size(), -1);

		for (int i = 0; i < (int)nums1.size(); i++) {
			auto j = std::find(nums2.begin(), nums2.end(), nums1[i]);

			while (j != nums2.end()) {
				if (*j > nums1[i]) {
					ans[i] = *j;
					break;
				}
				j++; 
			}
		}

		return ans;
	}
};
