/*
 * 802. Find Eventual Safe States (Medium)
 *
 * https://leetcode.com/problems/find-eventual-safe-states/
 *
 * There is a directed graph of n nodes with each node labeled from 0 to
 * n - 1. The graph is represented by a 0-indexed 2D integer array graph
 * where graph[i] is an integer array of nodes adjacent to node i, meaning
 * there is an edge from node i to each node in graph[i].
 *
 * A node is a terminal node if there are no outgoing edges. A node is a safe
 * node if every possible path starting from that node leads to a terminal
 * node (or another safe node).
 *
 * Return an array containing all the safe nodes of the graph. The answer
 * should be sorted in ascending order.
 *
 * Example 1:
 * Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
 * Output: [2,4,5,6]
 * Explanation: The given graph is shown above.
 * Nodes 5 and 6 are terminal nodes as there are no outgoing edges from
 * either of them.
 * Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5
 * or 6.
 *
 * Example 2:
 * Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
 * Output: [4]
 * Explanation:
 * Only node 4 is a terminal node, and every path starting at node 4 leads
 * to node 4.
 *
 * Constraints:
 * - n == graph.length
 * - 1 <= n <= 10^4
 * - 0 <= graph[i].length <= n
 * - 0 <= graph[i][j] <= n - 1
 * - graph[i] is sorted in a strictly increasing order.
 * - The graph may contain self-loops.
 * - The number of edges in the graph will be in the range [1, 4 * 10^4].
 */

#include <cassert>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        // TODO: implement
        throw "not implemented";
    }
};

// Returns [first, first + 1, ..., last].
vector<int> range_inclusive(int first, int last) {
    vector<int> values(last - first + 1);
    iota(values.begin(), values.end(), first);
    return values;
}

int main() {
    Solution solution;

    // Examples from the problem statement.
    {
        vector<vector<int>> graph = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
        assert(solution.eventualSafeNodes(graph) == vector<int>({2, 4, 5, 6}));
    }

    {
        vector<vector<int>> graph = {{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}};
        assert(solution.eventualSafeNodes(graph) == vector<int>({4}));
    }

    // Smallest graphs: a self-loop, a single edge, and a two-node cycle.
    {
        vector<vector<int>> graph = {{0}};
        assert(solution.eventualSafeNodes(graph).empty());
    }

    {
        vector<vector<int>> graph = {{1}, {}};
        assert(solution.eventualSafeNodes(graph) == vector<int>({0, 1}));
    }

    {
        vector<vector<int>> graph = {{1}, {0}};
        assert(solution.eventualSafeNodes(graph).empty());
    }

    // A self-loop makes a node unsafe even when it also reaches a terminal node.
    {
        vector<vector<int>> graph = {{0, 1}, {}};
        assert(solution.eventualSafeNodes(graph) == vector<int>({1}));
    }

    // Every node on a chain to a terminal node is safe.
    {
        vector<vector<int>> graph = {{1}, {2}, {3}, {}};
        assert(solution.eventualSafeNodes(graph) == vector<int>({0, 1, 2, 3}));
    }

    // A node that only leads into a cycle is unsafe.
    {
        vector<vector<int>> graph = {{1}, {2}, {1}};
        assert(solution.eventualSafeNodes(graph).empty());
    }

    // Reaching the same safe node along two paths is not a cycle.
    {
        vector<vector<int>> graph = {{1, 2}, {3}, {3}, {}};
        assert(solution.eventualSafeNodes(graph) == vector<int>({0, 1, 2, 3}));
    }

    // Nodes on a cycle stay unsafe even if the cycle also has an exit.
    {
        vector<vector<int>> graph = {{1}, {2}, {0, 3}, {}, {3}};
        assert(solution.eventualSafeNodes(graph) == vector<int>({3, 4}));
    }

    // One edge into a cycle is enough to make a node unsafe.
    {
        vector<vector<int>> graph = {{}, {0, 2}, {3}, {2}};
        assert(solution.eventualSafeNodes(graph) == vector<int>({0}));
    }

    // Disconnected components are judged independently.
    {
        vector<vector<int>> graph = {{1}, {}, {3}, {2}, {5}, {}};
        assert(solution.eventualSafeNodes(graph) == vector<int>({0, 1, 4, 5}));
    }

    const int n = 10000;

    // 10^4-node chain ending at a terminal node: everything is safe.
    {
        vector<vector<int>> graph(n);
        for (int i = 0; i < n - 1; i++) {
            graph[i] = {i + 1};
        }

        assert(solution.eventualSafeNodes(graph) == range_inclusive(0, n - 1));
    }

    // 10^4-node cycle: nothing is safe.
    {
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            graph[i] = {(i + 1) % n};
        }

        assert(solution.eventualSafeNodes(graph).empty());
    }

    // A long chain to a terminal node, followed by a separate long cycle.
    {
        vector<vector<int>> graph(n);
        for (int i = 0; i < n / 2; i++) {
            graph[i] = {i + 1};
        }
        for (int i = n / 2 + 1; i < n - 1; i++) {
            graph[i] = {i + 1};
        }
        graph[n - 1] = {n / 2 + 1};

        assert(solution.eventualSafeNodes(graph) == range_inclusive(0, n / 2));
    }

    // Close to 4 * 10^4 edges: each node points to the next four nodes.
    {
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= i + 4 && j < n; j++) {
                graph[i].push_back(j);
            }
        }

        assert(solution.eventualSafeNodes(graph) == range_inclusive(0, n - 1));
    }

    return 0;
}
