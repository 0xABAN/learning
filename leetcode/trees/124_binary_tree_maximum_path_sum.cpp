#include <algorithm> 
#include <limits> 

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
    int maxPathSum(TreeNode* root) {
        /**
         * how to get one non branching tree? 
         * find the 2 path's last shared node  
         * 
         * for the left path: find the max left path 
         * for the right path: find the max right path
         * 
         * to find one left path, just choose either left or right at any opportunity
         * that leaves two decisions at each step: left or right 
         *
         * base case: 
         * no node -> return 0
         * 
         * 1. a -> null -> null return a 
         * 2. a -> b -> null go to b & were back at case 1. 
         * 3. a -> b -> c choose max(a, b). 
         * 4. we always keep the biggest a + b as the answer, we can use a global var
         * 
         * one thing left: how can i make sure an invalid parent doesn't overwrite a
         * superior child? through the stored maximum
         *
         * [1,2,null,3,null,4,null,5]
         *      1
         *     / 
         *    2
         *   /
         *  3
         * /
         *4
         * */
        
        int ans = numeric_limits<int>::lowest(); 
        const auto& dfs = [&ans](auto&& self, TreeNode* node) -> int {
            if (!node) return 0;

            int left = max(0, self(self, node->left)); 
            int right = max(0, self(self, node->right));  
            int cur = node->val+left+right;
            
            ans = max(ans, cur);
            return node->val + max(left, right); 
        }; 

        dfs(dfs, root);
        return ans; 
    }
};
