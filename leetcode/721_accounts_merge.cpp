#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm> 

using namespace std;

class Solution {
public:
	vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
		/*
		 * merge accs belonging to the same person
		 * same person: share email address
		 * email: person 
		 * 2nd pass: reread the same list. if the emails are already in the map, then we can use them for the
		 * newest vector 
		 * connect every email to every other email
		 * */
		
		unordered_map<string, string> emails; 
		unordered_map<string, vector<string>> neighbors; 	
		vector<vector<string>> ans; 
		
		for(auto& acc : accounts) {
			// name : emails 
			string name = acc[0]; 
			
			for(int i = 1; i < acc.size(); i++) emails[acc[i]] = name; 
			
			for(int i = 2; i < acc.size(); i++) {
				neighbors[acc[1]].push_back(acc[i]);  
				neighbors[acc[i]].push_back(acc[1]); 
			}
		}
		
		unordered_set<string> seen; 
		const auto& dfs = [&neighbors, &seen](auto&& self, string start, vector<string>& v) -> void {
			// gives me all of the neighbors (all share emails to same person)
			if(seen.contains(start)) return; 
			seen.insert(start); 
			v.push_back(start);
			
			for(const string& neighbor : neighbors[start]){
				self(self, neighbor, v);
			}	
		}; 

		for(const auto& [email, name] : emails) {
			vector<string> acc{name}; 	
			vector<string> emails; 
			
			if(seen.contains(email)) continue;  
			dfs(dfs, email, emails); 
			
			sort(emails.begin(), emails.end());
			acc.insert(acc.end(), emails.begin(), emails.end());

			ans.push_back(acc); 
		}		
		
		return ans;
	}
};
