#include <vector>
#include <algorithm> 

using namespace std;

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		sort(intervals.begin(), intervals.end());
		vector<vector<int>> merged{intervals[0]};
		
		for(int i = 1; i < intervals.size();i++) {
			auto& x = intervals[i]; 
			auto& y = stack.back(); 

			if(x[1] <= y[1]){
				continue;
			} else if(x[0] <= y[1]){
				y[1] = x[1]; 
			} else {
				stack.push_back(x);
			}
		}

		return stack; 
	}
};
