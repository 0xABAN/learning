#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	bool isValid(string s) {
		// "()[]{}"
		// open brackets are closed by same bracket type 
		/*
		* i can loop twice, outer for loop loops through individual brackets, 
		* inner for loop scans for next open / close bracket type 
		* we store the number still left open after this amount 
		*
		*  would need a map storing bracket types "{": "}"
		*  
		*  this would be O(N^2)
		*
		*  could possibly be optimized to O(N) 
		*  likely using some sort of stack structure 
		*
		*  [{, }, [, ]]
		*
		*  we push the first seen bracket to some stack 
		*
		*  [{]
		*
		*  we're looking for the next char to be }, if it is, pop stack, if isn't, add new to stack
		*
		* "()[]{}" -> [(, ]
		* */ 
		
		unordered_map<char, char> m = {{')', '('}, {'}', '{'}, {']', '['}};
		vector<char> stack; 

		for(char c : s){
			if(stack.empty() || stack.back() != m[c])	{
				stack.push_back(c); 
				continue; 
			}
			stack.pop_back(); 
		}
		
		return stack.empty();
	}
};
