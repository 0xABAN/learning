"""133. Clone Graph (Medium).

https://leetcode.com/problems/clone-graph/

Given a reference of a node in a connected undirected graph.

Return a deep copy (clone) of the graph.

Each node in the graph contains a value (int) and a list (List[Node]) of its
neighbors.

    class Node {
        public int val;
        public List<Node> neighbors;
    }

Test case format:

For simplicity, each node's value is the same as the node's index
(1-indexed). For example, the first node with val == 1, the second node with
val == 2, and so on. The graph is represented in the test case using an
adjacency list.

An adjacency list is a collection of unordered lists used to represent a
finite graph. Each list describes the set of neighbors of a node in the
graph.

The given node will always be the first node with val = 1. You must return
the copy of the given node as a reference to the cloned graph.

Example 1:
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).

Example 2:
Input: adjList = [[]]
Output: [[]]
Explanation: Note that the input contains one empty list. The graph consists
of only one node with val = 1 and it does not have any neighbors.

Example 3:
Input: adjList = []
Output: []
Explanation: This is an empty graph, it does not have any nodes.

Constraints:
- The number of nodes in the graph is in the range [0, 100].
- 1 <= Node.val <= 100
- Node.val is unique for each node.
- There are no repeated edges and no self-loops in the graph.
- The Graph is connected and all nodes can be visited starting from the
  given node.
"""

from __future__ import annotations
    
class Node:
    def __init__(self, val: int = 0, neighbors: list[Node] | None = None) -> None:
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []


class Solution:
    def cloneGraph(self, node: Node | None) -> Node | None:
        if not node: return None 

        def dfs(res, node): 
            for real in node.neighbors: 
                if real not in g: 
                    copy = Node(real.val)
                    g[real] = copy
                    
                    dfs(copy, real)

                res.neighbors.append(g[real]) 
        
        res = Node(node.val)
        g = {node: res}
        
        dfs(res, node)
        return res


def build_graph(adj_list: list[list[int]]) -> Node | None:
    """Build a graph from LeetCode's 1-indexed adjacency list and return node 1."""
    if not adj_list:
        return None

    nodes = [Node(val) for val in range(1, len(adj_list) + 1)]

    for node, neighbor_vals in zip(nodes, adj_list):
        node.neighbors = [nodes[val - 1] for val in neighbor_vals]

    return nodes[0]


def collect_nodes(start: Node) -> list[Node]:
    """Return every distinct node object reachable from start, compared by identity."""
    found = {id(start): start}
    stack = [start]

    while stack:
        node = stack.pop()

        for neighbor in node.neighbors:
            if id(neighbor) not in found:
                found[id(neighbor)] = neighbor
                stack.append(neighbor)

    return list(found.values())


def to_adj_list(start: Node | None) -> list[list[int]]:
    """Convert a graph back into LeetCode's adjacency-list format."""
    if start is None:
        return []

    nodes = sorted(collect_nodes(start), key=lambda node: node.val)
    return [[neighbor.val for neighbor in node.neighbors] for node in nodes]


def assert_clones(adj_list: list[list[int]]) -> None:
    """Clone the graph described by adj_list and check that the copy is deep and exact."""
    original = build_graph(adj_list)
    clone = Solution().cloneGraph(original)

    # The clone must have the same shape as the input, starting from node 1.
    assert to_adj_list(clone) == adj_list

    if original is None:
        assert clone is None
        return

    assert clone is not None
    assert clone.val == 1

    # A deep copy must not reuse any node object from the original graph.
    original_ids = {id(node) for node in collect_nodes(original)}
    assert all(id(node) not in original_ids for node in collect_nodes(clone))

    # Cloning must leave the original graph untouched.
    assert to_adj_list(original) == adj_list


def main() -> None:
    # Examples from the problem statement.
    assert_clones([[2, 4], [1, 3], [2, 4], [1, 3]])
    assert_clones([[]])
    assert_clones([])

    # Smallest graphs with edges.
    assert_clones([[2], [1]])
    assert_clones([[2, 3], [1, 3], [1, 2]])

    # Neighbor order is not sorted and must be preserved.
    assert_clones([[3, 2], [1, 3], [2, 1]])
    assert_clones([[4, 2, 3], [1], [1], [1]])

    # Trees: a path, a star, and a start node that is a leaf.
    assert_clones([[2], [1, 3], [2, 4], [3]])
    assert_clones([[2, 3, 4, 5], [1], [1], [1], [1]])
    assert_clones([[2], [1, 3, 4], [2], [2]])

    # Cycles mixed with tree branches.
    assert_clones([[2, 3], [1, 3], [1, 2, 4], [3]])
    assert_clones([[2, 3, 4, 5], [1, 3], [1, 2], [1, 5], [1, 4]])

    # Complete graph on 4 nodes.
    assert_clones([[2, 3, 4], [1, 3, 4], [1, 2, 4], [1, 2, 3]])

    # 100 nodes: the longest path, the longest cycle, and the densest graph.
    n = 100
    middle = [[val - 1, val + 1] for val in range(2, n)]

    assert_clones([[2]] + middle + [[n - 1]])
    assert_clones([[n, 2]] + middle + [[n - 1, 1]])
    assert_clones([[other for other in range(1, n + 1) if other != val] for val in range(1, n + 1)])


if __name__ == "__main__":
    main()
