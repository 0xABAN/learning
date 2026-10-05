#include <iostream> 
#include <vector> 

using namespace std; 

class Solution { 
public:
	int singleNumber(vector<int>& nums) { 
		int pivot = 0; 

		for (int x : nums) { 
			pivot = x ^ pivot;
		}
		return pivot;
	}
};
