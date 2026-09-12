struct TreeNode{
	int val; 
	TreeNode* left;
	TreeNode* right; 
	
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		const auto& dfs = [p, q](auto&& self, TreeNode* node) -> TreeNode* {
			if(!node || node == p || node == q) return node; 
			
			TreeNode* left = self(self, node->left);
			TreeNode* right = self(self, node->right);
			
			if(left && right) return node; 

			return left ? left : right; 
		};
		
		return dfs(dfs, root);	
	}
};
