"""4100. Minimum Cost Path With Even XOR Parity (Hard).

https://leetcode.com/problems/minimum-cost-path-with-even-xor-parity/

You are given a tree with n nodes numbered from 0 to n - 1, represented by a
2D integer array edges. Each edges[i] = [ui, vi, ci] represents an edge
between nodes ui and vi with cost ci.

You are also given an integer array values of length n, where values[i] is
the value of node i.

A path between two distinct nodes is Balanced-XOR if the bitwise XOR of the
values of all nodes on the path, including both endpoints, has an even
number of set bits.

The cost of a path is the sum of its edge costs.

Return the minimum cost of a Balanced-XOR path. If no such path exists,
return -1.

The number 0 has zero set bits.

Example 1:
Input: edges = [[0,1,4],[0,2,6],[0,3,3],[3,4,5]], values = [3,1,7,1,3]
Output: 7
Explanation:
    Balanced-XOR Path   XOR Value                   Total Cost
    1 - 0 - 2           1 XOR 3 XOR 7 = 5           4 + 6 = 10
    1 - 0 - 3           1 XOR 3 XOR 1 = 3           4 + 3 = 7
    1 - 0 - 3 - 4       1 XOR 3 XOR 1 XOR 3 = 0     4 + 3 + 5 = 12
    2 - 0 - 3           7 XOR 3 XOR 1 = 5           6 + 3 = 9
    2 - 0 - 3 - 4       7 XOR 3 XOR 1 XOR 3 = 6     6 + 3 + 5 = 14
The minimum cost is 7, achieved by the path 1 - 0 - 3. Thus, the answer
is 7.

Example 2:
Input: edges = [[0,1,5],[1,2,10]], values = [1,7,3]
Output: 5
Explanation:
    Balanced-XOR Path   XOR Value                   Total Cost
    0 - 1               1 XOR 7 = 6                 5
    0 - 1 - 2           1 XOR 7 XOR 3 = 5           5 + 10 = 15
The minimum cost is 5, achieved by the path 0 - 1. Thus, the answer is 5.

Example 3:
Input: edges = [[0,1,5],[0,2,7],[0,3,9]], values = [1,3,5,9]
Output: -1
Explanation:
- Every path between two distinct nodes has an XOR value with an odd number
  of set bits.
- Therefore, no Balanced-XOR path exists, so the answer is -1.

Constraints:
- 2 <= n <= 10^5
- edges.length == n - 1
- edges[i] = [ui, vi, ci]
  - 0 <= ui, vi <= n - 1
  - 1 <= ci <= 10^9
- values.length == n
- 1 <= values[i] <= 10^9
- edges represents a valid tree.
"""


class Solution:
    def minActivationCost(self, edges: list[list[int]], values: list[int]) -> int:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    def check(edges: list[list[int]], values: list[int], expected: int) -> None:
        assert solution.minActivationCost(edges, values) == expected

    # Examples from the problem statement.
    check([[0, 1, 4], [0, 2, 6], [0, 3, 3], [3, 4, 5]], [3, 1, 7, 1, 3], 7)
    check([[0, 1, 5], [1, 2, 10]], [1, 7, 3], 5)
    check([[0, 1, 5], [0, 2, 7], [0, 3, 9]], [1, 3, 5, 9], -1)

    # Two nodes: 1 XOR 2 = 3 has two set bits.
    check([[0, 1, 7]], [1, 2], 7)

    # Two nodes: 1 XOR 3 = 2 has one set bit.
    check([[1, 0, 4]], [1, 3], -1)

    # Equal values XOR to 0, at the maximum edge cost.
    check([[0, 1, 10**9]], [10**9, 10**9], 10**9)

    # Three-node path with no Balanced-XOR path.
    check([[0, 1, 1], [1, 2, 1]], [3, 1, 5], -1)

    # The cheaper path 1 - 2 - 3 beats the Balanced-XOR edge 0 - 1.
    check([[0, 1, 100], [1, 2, 2], [2, 3, 3]], [1, 2, 3, 4], 5)

    # The answer exceeds the 32-bit signed integer range.
    check([[0, 1, 10**9], [1, 2, 10**9]], [1, 3, 1], 2 * 10**9)

    # Large node values; the cheapest edge is not Balanced-XOR.
    check(
        [[0, 1, 8], [1, 2, 3], [2, 3, 4], [1, 4, 6]],
        [10**9, 999_999_999, 2**29 + 1, 123_456_789, 2**29],
        4,
    )

    # Edges in arbitrary order and orientation; the three cheapest edges are
    # not Balanced-XOR.
    check(
        [[5, 2, 9], [3, 5, 4], [7, 3, 2], [0, 7, 6], [3, 1, 8], [6, 0, 5], [4, 6, 1]],
        [12, 5, 9, 14, 8, 3, 3, 10],
        5,
    )

    n = 10**5

    # 10^5-node star with no Balanced-XOR path.
    check([[0, leaf, leaf] for leaf in range(1, n)], [1] + [3] * (n - 1), -1)

    # 10^5-node star whose cheapest leaves cost 1 and 2.
    check([[leaf, 0, n - leaf] for leaf in range(1, n)], [3] + [1] * (n - 1), 3)

    # 10^5-node path with equal values; the last edge is cheapest.
    check(
        [[i, i + 1, 10**9 - i] for i in range(n - 1)],
        [42] * n,
        10**9 - (n - 2),
    )

    # 10^5-node path with alternating values and maximum edge costs.
    check(
        [[i, i + 1, 10**9] for i in range(n - 1)],
        [6 if i % 2 == 0 else 7 for i in range(n)],
        2 * 10**9,
    )


if __name__ == "__main__":
    main()
