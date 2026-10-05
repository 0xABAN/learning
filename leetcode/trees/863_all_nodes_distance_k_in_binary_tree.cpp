#include <vector>
#include <unordered_map>
#include <unordered_set> 
#include <deque> 
#include <utility> 

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
		unordered_map<TreeNode*, vector<TreeNode*>> graph; 
		const auto& construct_graph = [&graph](auto&& self, TreeNode* node) -> void {
			if(!node) return;
			
			if(node->left){
				graph[node].push_back(node->left);
				graph[node->left].push_back(node);
			}
			if(node->right){
				graph[node].push_back(node->right);
				graph[node->right].push_back(node);
			}
			
			self(self, node->left);
			self(self, node->right); 
		}; 

		construct_graph(construct_graph, root); 
		
		deque<pair<TreeNode*, int>> q{{target, 0}};
		unordered_set<TreeNode*> seen; 
		vector<int> ans; 
	
		while(!q.empty()){
			auto [node, dist] = q.front(); 
			q.pop_front(); 
			
			seen.insert(node); 
			if(dist == k) ans.push_back(node->val); 
			
			for(TreeNode* neighbor : graph[node]){
				if(!seen.contains(neighbor)) {
					q.push_back({neighbor, dist+1});	
				}
			}
		}
		
		return ans; 
	}
};
