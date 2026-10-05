#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
	string shortestBeautifulSubstring(string s, int k) {
		int l = 0, c = 0; 
		bool valid = false; 
		string ans = s; 
		
		for (int r = 0; r < s.size(); r++) {
			if (s[r] == '1') {
				c++; 
			}

			if (c == k) {
				valid = true; 
				// filter out the leading 0's 
				while (s[l] != '1') {
					l++; 
				}
				
				int n = r-l+1; 
				string cur = s.substr(l, n); 
				if (n < ans.size() || (n == ans.size() && cur < ans)) {
					ans = cur; 
				}
				
				l++; 
				c--; 
			}
		}
		
		if (!valid) {
			return ""; 
		} 
		return ans; 
	}
};
