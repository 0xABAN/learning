"""687. Longest Univalue Path (Medium).

https://leetcode.com/problems/longest-univalue-path/

LeetCode version of a problem described in a June 2026 Google L4 interview
report (candidate-reported, not an official Google question list):
https://leetcode.com/discuss/post/8325811/google-l4-interview-experience-chances-b-3qmq/

Given the root of a binary tree, return the length of the longest path
where every node in the path has the same value. This path may or may not
pass through the root.

The length of a path is the number of edges between its nodes.

Example 1:
Input: root = [5,4,5,1,1,null,5]
Output: 2
Explanation: The longest path connects three nodes with value 5.

Example 2:
Input: root = [1,4,5,4,4,null,5]
Output: 2
Explanation: The longest path connects three nodes with value 4.

Constraints:
- The number of nodes is in the range [0, 10000].
- -1000 <= Node.val <= 1000
- The depth of the tree will not exceed 1000.
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
    def longestUnivaluePath(self, root: TreeNode | None) -> int:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    assert solution.longestUnivaluePath(None) == 0
    assert solution.longestUnivaluePath(TreeNode(8)) == 0
    assert solution.longestUnivaluePath(
        TreeNode(0, TreeNode(-1000), TreeNode(1000))
    ) == 0
    assert solution.longestUnivaluePath(
        TreeNode(7, TreeNode(7), TreeNode(7))
    ) == 2
    assert solution.longestUnivaluePath(
        TreeNode(1000, TreeNode(1000), TreeNode(-1000))
    ) == 1

    root = TreeNode(
        -3,
        TreeNode(-3, TreeNode(-3)),
        TreeNode(-3, None, TreeNode(-3)),
    )
    assert solution.longestUnivaluePath(root) == 4

    root = TreeNode(
        1,
        TreeNode(2, TreeNode(2, TreeNode(2)), TreeNode(2)),
        TreeNode(3),
    )
    assert solution.longestUnivaluePath(root) == 3

    root = TreeNode(
        2,
        TreeNode(1, TreeNode(2)),
        TreeNode(3, None, TreeNode(2)),
    )
    assert solution.longestUnivaluePath(root) == 0

    root = TreeNode(6)
    for _ in range(999):
        root = TreeNode(6, root)
    assert solution.longestUnivaluePath(root) == 999


if __name__ == "__main__":
    main()
