"""543. Diameter of Binary Tree (Easy).

https://leetcode.com/problems/diameter-of-binary-tree/

Given the root of a binary tree, return the length of its diameter.

The diameter is the length of the longest path between any two nodes in
the tree. This path may or may not pass through the root. Path length is
measured by the number of edges, not the number of nodes.

Example 1:
Input: root = [1, 2, 3, 4, 5]
Output: 3
Explanation: The paths [4, 2, 1, 3] and [5, 2, 1, 3] each have 3 edges.

Example 2:
Input: root = [1, 2]
Output: 1

Constraints:
- The number of nodes is in the range [1, 10000].
- -100 <= Node.val <= 100

if we have no node: 
    return 0 

diameter = max(diameter, l + r) 
return 1 + max(l, r)
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
    def diameterOfBinaryTree(self, root: TreeNode | None) -> int:
        self.diameter = 0 

        def helper(node): 
            if not node: 
                return 0 
            
            l = r = 0 
            if node.left:
                l = 1 + helper(node.left)
            if node.right:
                r = 1 + helper(node.right)
            
            self.diameter = max(self.diameter, l + r)
            return max(l, r)

        helper(root)
        return self.diameter


        

def main() -> None:
    solution = Solution()

    assert solution.diameterOfBinaryTree(TreeNode(0)) == 0
    assert solution.diameterOfBinaryTree(
        TreeNode(-100, None, TreeNode(100))
    ) == 1
    assert solution.diameterOfBinaryTree(
        TreeNode(5, TreeNode(5), TreeNode(5))
    ) == 2

    root = TreeNode(
        0,
        TreeNode(1, TreeNode(2), TreeNode(3)),
        TreeNode(4, TreeNode(5), TreeNode(6)),
    )
    assert solution.diameterOfBinaryTree(root) == 4

    root = TreeNode(0, TreeNode(1, TreeNode(2, TreeNode(3, TreeNode(4)))))
    assert solution.diameterOfBinaryTree(root) == 4

    root = TreeNode(0, None, TreeNode(1, TreeNode(2, None, TreeNode(3))))
    assert solution.diameterOfBinaryTree(root) == 3

    root = TreeNode(
        0,
        TreeNode(
            1,
            TreeNode(2, TreeNode(3, TreeNode(4))),
            TreeNode(5, None, TreeNode(6, None, TreeNode(7))),
        ),
    )
    assert solution.diameterOfBinaryTree(root) == 6


if __name__ == "__main__":
    main()
