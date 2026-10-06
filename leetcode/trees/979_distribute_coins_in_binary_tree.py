"""979. Distribute Coins in Binary Tree (Medium).

https://leetcode.com/problems/distribute-coins-in-binary-tree/

You are given the root of a binary tree with n nodes where each node in the
tree has node.val coins. There are n coins in total throughout the whole
tree.

In one move, we may choose two adjacent nodes and move one coin from one
node to another. A move may be from parent to child, or from child to
parent.

Return the minimum number of moves required to make every node have exactly
one coin.

Example 1:
Input: root = [3,0,0]
Output: 2
Explanation: From the root of the tree, we move one coin to its left child,
and one coin to its right child.

Example 2:
Input: root = [0,3,0]
Output: 3
Explanation: From the left child of the root, we move two coins to the root
[taking two moves]. Then, we move one coin from the root of the tree to the
right child.

Constraints:
- The number of nodes in the tree is n.
- 1 <= n <= 100
- 0 <= Node.val <= n
- The sum of all Node.val is n.
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
    def distributeCoins(self, root: TreeNode | None) -> int:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    assert solution.distributeCoins(TreeNode(1)) == 0
    assert solution.distributeCoins(TreeNode(2, TreeNode(0))) == 1
    assert solution.distributeCoins(TreeNode(0, None, TreeNode(2))) == 1

    assert solution.distributeCoins(TreeNode(3, TreeNode(0), TreeNode(0))) == 2
    assert solution.distributeCoins(TreeNode(0, TreeNode(3), TreeNode(0))) == 3
    assert solution.distributeCoins(TreeNode(1, TreeNode(0), TreeNode(2))) == 2

    root = TreeNode(1, TreeNode(0, None, TreeNode(3)), TreeNode(0))
    assert solution.distributeCoins(root) == 4

    root = TreeNode(
        1,
        TreeNode(1, TreeNode(1), TreeNode(1)),
        TreeNode(1, TreeNode(1), TreeNode(1)),
    )
    assert solution.distributeCoins(root) == 0

    root = TreeNode(
        0,
        TreeNode(2, TreeNode(0), TreeNode(1)),
        TreeNode(2),
    )
    assert solution.distributeCoins(root) == 2

    root = TreeNode(
        0,
        TreeNode(0, TreeNode(7), TreeNode(0)),
        TreeNode(0, TreeNode(0), TreeNode(0)),
    )
    assert solution.distributeCoins(root) == 16

    root = TreeNode(0, TreeNode(0, TreeNode(0, TreeNode(4))))
    assert solution.distributeCoins(root) == 6

    root = TreeNode(4, TreeNode(0, TreeNode(0, TreeNode(0))))
    assert solution.distributeCoins(root) == 6

    root = TreeNode(0)
    for _ in range(98):
        root = TreeNode(0, root)
    root = TreeNode(100, root)
    assert solution.distributeCoins(root) == 4950


if __name__ == "__main__":
    main()
