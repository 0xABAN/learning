#include <string>
#include <unordered_set>
#include <algorithm> 

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		// wwkew 
		// {w, k, e, 	
		unordered_set<char> seen; 
		int l = 0, ans = 0; 	
		
		for(int r = 0; r < s.size(); r++){
			while(seen.contains(s[r])) {
				seen.erase(s[l]);
				l++; 
			}

			seen.insert(s[r]); // b
			ans = max(ans,r-l+1); // 1 
		}
		
		return ans;
	}
};
