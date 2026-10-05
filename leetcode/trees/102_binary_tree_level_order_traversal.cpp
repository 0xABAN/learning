#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int val = 0, TreeNode* left = nullptr, TreeNode* right = nullptr)
		: val(val), left(left), right(right) {}
};

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if(!root) return {}; 
		
		vector<vector<int>> ans{{root->val}}; 
		vector<TreeNode*> q; 
		q.push_back(root); 
		
		while(!q.empty()){
			vector<TreeNode*> level; 

			for(TreeNode* node : q) {
				if(node->left) level.push_back(node->left); 
				if(node->right) level.push_back(node->right); 	
			}
			q.clear(); 
			
			if(!level.empty()) {
				ans.push_back({});
				for(TreeNode* node : level) {
					q.push_back(node);
					ans.back().push_back(node->val); 
				} 	
			}
		}
		
		return ans; 
	}
};
