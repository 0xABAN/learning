#include <string>
#include <unordered_map>

using namespace std;

class Logger {
public:
	unordered_map<string, int> map; 
	
	bool shouldPrintMessage(int timestamp, string message) {
		// we only rate limit the same message, not different messages 
		// we will just use a hashmap	

		if(map.contains(message) && timestamp - map[message] < 10) return false; 
		map[message] = timestamp; 
		return true; 
	}
};
