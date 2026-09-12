#include <algorithm>

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
	int maxDepth(TreeNode* root) {
		const auto& dfs = [](auto&& self, TreeNode* node){
			if (!node) return 0; 

			int left = self(self, node->left);
			int right = self(self, node->right); 

			return max(left, right) + 1;
		};
		
		return dfs(dfs, root);
	}
};
