#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <utility>
#include <iostream> 

using namespace std;

class Solution {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		/*
		 * seems like a graph-type problem 
		 * we can try to create an adjacency list of words
		 * hit -> all words 1 off from hit 
		 * and so on for all other words 
		 * complexity of this would be O(N^2*M) bc need compare each word with every other word
		 * can probably do bfs after & find distance length by following adjacency list 
		 * */
		
		if(find(wordList.begin(), wordList.end(), endWord) == wordList.end()) return 0; 
		
		wordList.push_back(beginWord);
		unordered_map<string, vector<string>> adj; 

		for(int i = 0; i < wordList.size(); i++) {
			for(int j = i+1; j < wordList.size(); j++) {
				// check chars 

				int diff = 0; 
				for(int k = 0; k < wordList[i].size(); k++) {
					if (wordList[i][k] != wordList[j][k]) diff++; 
				}

				if(diff == 1) {
					adj[wordList[i]].push_back(wordList[j]);
					adj[wordList[j]].push_back(wordList[i]);
				}
			}
		}
		
		// bfs here: ("hot", 2)
		const auto& bfs = [&adj, endWord](string start){			
			unordered_set<string> seen{start}; 
			deque<pair<string, int>> q{{start, 1}}; 
			
			while(!q.empty()){
				auto [word, dist] = q.front(); 
				q.pop_front();

				if(word == endWord) return dist; 

				for(string neighbor : adj[word]){
					if(!seen.contains(neighbor)){
						seen.insert(neighbor);
						q.push_back({neighbor, dist+1});
					}
				}
			}	
			
			return 0; 
		};
		
		return bfs(beginWord);
	}
};
