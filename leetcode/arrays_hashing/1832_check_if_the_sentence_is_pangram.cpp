#include <string>
#include <unordered_set> 
using namespace std;

class Solution {
public:
	bool checkIfPangram(string sentence) {
	 	unordered_set<char>	s; 

		for (char c : sentence) {
			s.insert(c); 
		}

		return s.size() == 26;
	}
};
