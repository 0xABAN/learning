#include <cmath>
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
    bool isBalanced(TreeNode* root) {
        bool balanced = true; 
        const auto& dfs = [&balanced](auto&& self, TreeNode* node) -> int {
            if (!node) return 0; 
            
            int left = self(self, node->left);
            int right = self(self, node->right);
            
            if(abs(right-left)>1) balanced = false; 
            return 1+max(left, right); 
        }; 
        
        dfs(dfs, root);
        return balanced;
    }
};
