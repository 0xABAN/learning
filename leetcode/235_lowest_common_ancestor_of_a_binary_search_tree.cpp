struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		const auto& dfs = [p, q](auto&& self, TreeNode* node) -> TreeNode* {
			if (!node) return node; 
			
			if (node->val > p->val && node->val > q->val) {
				return self(self, node->left);				
			} else if (node->val < p->val && node->val < q->val) {
				return self(self, node->right);	
			} else {
				return node; 	
			}
		};
		
		return dfs(dfs, root); 
	}
};
