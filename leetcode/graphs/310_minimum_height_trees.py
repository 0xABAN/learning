"""310. Minimum Height Trees (Medium).

https://leetcode.com/problems/minimum-height-trees/

A tree is an undirected graph in which any two vertices are connected by
exactly one path. In other words, any connected graph without simple cycles
is a tree.

Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1
edges where edges[i] = [ai, bi] indicates that there is an undirected edge
between the two nodes ai and bi in the tree, you can choose any node of the
tree as the root. When you select a node x as the root, the result tree has
height h. Among all possible rooted trees, those with minimum height (i.e.
min(h)) are called minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any
order.

The height of a rooted tree is the number of edges on the longest downward
path between the root and a leaf.

Example 1:
Input: n = 4, edges = [[1,0],[1,2],[1,3]]
Output: [1]
Explanation: As shown, the height of the tree is 1 when the root is the
node with label 1 which is the only MHT.

Example 2:
Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
Output: [3,4]

Constraints:
- 1 <= n <= 2 * 10^4
- edges.length == n - 1
- 0 <= ai, bi < n
- ai != bi
- All the pairs (ai, bi) are distinct.
- The given input is guaranteed to be a tree and there will be no repeated
  edges.
"""


class Solution:
    def findMinHeightTrees(self, n: int, edges: list[list[int]]) -> list[int]:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    # The answer may be returned in any order, so tests compare sorted results.
    def check(n: int, edges: list[list[int]], expected: list[int]) -> None:
        assert sorted(solution.findMinHeightTrees(n, edges)) == expected

    # Examples from the problem statement.
    check(4, [[1, 0], [1, 2], [1, 3]], [1])
    check(6, [[3, 0], [3, 1], [3, 2], [3, 4], [5, 4]], [3, 4])

    # A single node has no edges.
    check(1, [], [0])

    # Two nodes are equally good roots.
    check(2, [[0, 1]], [0, 1])

    # Paths with an odd and an even number of nodes.
    check(3, [[0, 1], [1, 2]], [1])
    check(4, [[0, 1], [1, 2], [2, 3]], [1, 2])

    # A path whose labels are out of order: 3 - 1 - 4 - 0 - 2.
    check(5, [[3, 1], [1, 4], [4, 0], [0, 2]], [4])

    # A star is rooted at its center.
    check(5, [[0, 1], [0, 2], [0, 3], [0, 4]], [0])

    # The node with the most neighbors is not always the best root.
    check(7, [[0, 1], [1, 2], [2, 3], [3, 4], [1, 5], [1, 6]], [2])

    # Two adjacent best roots in a tree that is not a path.
    check(6, [[0, 1], [1, 2], [2, 3], [1, 4], [2, 5]], [1, 2])

    # Legs of lengths 3, 2, and 1 hanging off node 0.
    check(7, [[0, 1], [1, 2], [2, 3], [0, 4], [4, 5], [0, 6]], [0, 1])

    # 2 * 10^4-node path: two middle nodes.
    n = 20_000
    check(n, [[i, i + 1] for i in range(n - 1)], [n // 2 - 1, n // 2])

    # 19999-node path: one middle node.
    n = 19_999
    check(n, [[i, i + 1] for i in range(n - 1)], [n // 2])

    # 2 * 10^4-node star.
    n = 20_000
    check(n, [[leaf, 0] for leaf in range(1, n)], [0])

    # Complete binary tree with 2^14 - 1 nodes: only the root is best.
    n = 2**14 - 1
    check(n, [[(child - 1) // 2, child] for child in range(1, n)], [0])


if __name__ == "__main__":
    main()
