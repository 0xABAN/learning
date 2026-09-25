"""124. Binary Tree Maximum Path Sum (Hard).

https://leetcode.com/problems/binary-tree-maximum-path-sum/

A path in a binary tree is a sequence of nodes where each pair of adjacent
nodes in the sequence has an edge connecting them. A node can appear in the
sequence at most once. The path does not need to pass through the root.

The path sum is the sum of the values of the nodes in the path.

Given the root of a binary tree, return the maximum path sum of any
non-empty path.

Example 1:
Input: root = [1, 2, 3]
Output: 6
Explanation: The path 2 -> 1 -> 3 has a sum of 2 + 1 + 3 = 6.

Example 2:
Input: root = [-10, 9, 20, null, null, 15, 7]
Output: 42
Explanation: The path 15 -> 20 -> 7 has a sum of 15 + 20 + 7 = 42.

Constraints:
- The number of nodes is in the range [1, 3 * 10^4].
- -1000 <= Node.val <= 1000.

   1
  / \
 2   3

self.ans = float('-inf') 
node.val + (sum returned by child)

(as a result of the recursion)
... 

self.ans = max(self.ans, l + r + node.val) where l and r are the individual children sums 
return max(l, r)

   -5 -> ans = max(float('-inf'), -5) -> -5 

   -10
   /  \
  -3   -5 


"""

from __future__ import annotations


class TreeNode:
    def __init__(
        self,
        val: int = 0,
        left: TreeNode | None = None,
        right: TreeNode | None = None,
    ) -> None:
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxPathSum(self, root: TreeNode | None) -> int:
        """
        """
        
        self.ans = float('-inf')

        def helper(node): 
            if not node: 
                return 0
            
            l = max(0, helper(node.left))
            r = max(0, helper(node.right))
            
            self.ans = max(self.ans, node.val + l + r) # -3 
            return node.val + max(l, r) # -3  

        helper(root)
        return self.ans


def main() -> None:
    solution = Solution()

    assert solution.maxPathSum(
        TreeNode(1, TreeNode(2), TreeNode(3))
    ) == 6

    root = TreeNode(
        -10,
        TreeNode(9),
        TreeNode(20, TreeNode(15), TreeNode(7)),
    )
    assert solution.maxPathSum(root) == 42

    assert solution.maxPathSum(TreeNode(-5)) == -5
    assert solution.maxPathSum(
        TreeNode(-3, TreeNode(-2), TreeNode(-1))
    ) == -1
    assert solution.maxPathSum(
        TreeNode(2, TreeNode(-1), TreeNode(3))
    ) == 5

    root = TreeNode(
        5,
        TreeNode(4, TreeNode(11, TreeNode(7), TreeNode(2))),
        TreeNode(8, TreeNode(13), TreeNode(4, None, TreeNode(1))),
    )
    assert solution.maxPathSum(root) == 48


if __name__ == "__main__":
    main()
