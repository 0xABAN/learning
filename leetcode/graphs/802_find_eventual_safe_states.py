"""802. Find Eventual Safe States (Medium).

https://leetcode.com/problems/find-eventual-safe-states/

There is a directed graph of n nodes with each node labeled from 0 to n - 1.
The graph is represented by a 0-indexed 2D integer array graph where
graph[i] is an integer array of nodes adjacent to node i, meaning there is
an edge from node i to each node in graph[i].

A node is a terminal node if there are no outgoing edges. A node is a safe
node if every possible path starting from that node leads to a terminal node
(or another safe node).

Return an array containing all the safe nodes of the graph. The answer
should be sorted in ascending order.

Example 1:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: The given graph is shown above.
Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either
of them.
Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.

Example 2:
Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
Explanation:
Only node 4 is a terminal node, and every path starting at node 4 leads to
node 4.

Constraints:
- n == graph.length
- 1 <= n <= 10^4
- 0 <= graph[i].length <= n
- 0 <= graph[i][j] <= n - 1
- graph[i] is sorted in a strictly increasing order.
- The graph may contain self-loops.
- The number of edges in the graph will be in the range [1, 4 * 10^4].
"""


class Solution:
    def eventualSafeNodes(self, graph: list[list[int]]) -> list[int]:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    # Examples from the problem statement.
    assert solution.eventualSafeNodes([[1, 2], [2, 3], [5], [0], [5], [], []]) == [2, 4, 5, 6]
    assert solution.eventualSafeNodes([[1, 2, 3, 4], [1, 2], [3, 4], [0, 4], []]) == [4]

    # Smallest graphs: a self-loop, a single edge, and a two-node cycle.
    assert solution.eventualSafeNodes([[0]]) == []
    assert solution.eventualSafeNodes([[1], []]) == [0, 1]
    assert solution.eventualSafeNodes([[1], [0]]) == []

    # A self-loop makes a node unsafe even when it also reaches a terminal node.
    assert solution.eventualSafeNodes([[0, 1], []]) == [1]

    # Every node on a chain to a terminal node is safe.
    assert solution.eventualSafeNodes([[1], [2], [3], []]) == [0, 1, 2, 3]

    # A node that only leads into a cycle is unsafe.
    assert solution.eventualSafeNodes([[1], [2], [1]]) == []

    # Reaching the same safe node along two paths is not a cycle.
    assert solution.eventualSafeNodes([[1, 2], [3], [3], []]) == [0, 1, 2, 3]

    # Nodes on a cycle stay unsafe even if the cycle also has an exit.
    assert solution.eventualSafeNodes([[1], [2], [0, 3], [], [3]]) == [3, 4]

    # One edge into a cycle is enough to make a node unsafe.
    assert solution.eventualSafeNodes([[], [0, 2], [3], [2]]) == [0]

    # Disconnected components are judged independently.
    assert solution.eventualSafeNodes([[1], [], [3], [2], [5], []]) == [0, 1, 4, 5]

    n = 10_000

    # 10^4-node chain ending at a terminal node: everything is safe.
    graph = [[i + 1] for i in range(n - 1)] + [[]]
    assert solution.eventualSafeNodes(graph) == list(range(n))

    # 10^4-node cycle: nothing is safe.
    graph = [[(i + 1) % n] for i in range(n)]
    assert solution.eventualSafeNodes(graph) == []

    # A long chain to a terminal node, followed by a separate long cycle.
    half = n // 2
    graph = (
        [[i + 1] for i in range(half)]
        + [[]]
        + [[i + 1] for i in range(half + 1, n - 1)]
        + [[half + 1]]
    )
    assert solution.eventualSafeNodes(graph) == list(range(half + 1))

    # Close to 4 * 10^4 edges: each node points to the next four nodes.
    graph = [list(range(i + 1, min(i + 5, n))) for i in range(n)]
    assert solution.eventualSafeNodes(graph) == list(range(n))


if __name__ == "__main__":
    main()
