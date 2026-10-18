/*
 * 133. Clone Graph (Medium)
 *
 * https://leetcode.com/problems/clone-graph/
 *
 * Given a reference of a node in a connected undirected graph.
 *
 * Return a deep copy (clone) of the graph.
 *
 * Each node in the graph contains a value (int) and a list (List[Node]) of
 * its neighbors.
 *
 *     class Node {
 *         public int val;
 *         public List<Node> neighbors;
 *     }
 *
 * Test case format:
 *
 * For simplicity, each node's value is the same as the node's index
 * (1-indexed). For example, the first node with val == 1, the second node
 * with val == 2, and so on. The graph is represented in the test case using
 * an adjacency list.
 *
 * An adjacency list is a collection of unordered lists used to represent a
 * finite graph. Each list describes the set of neighbors of a node in the
 * graph.
 *
 * The given node will always be the first node with val = 1. You must return
 * the copy of the given node as a reference to the cloned graph.
 *
 * Example 1:
 * Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
 * Output: [[2,4],[1,3],[2,4],[1,3]]
 * Explanation: There are 4 nodes in the graph.
 * 1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
 * 2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
 * 3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
 * 4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
 *
 * Example 2:
 * Input: adjList = [[]]
 * Output: [[]]
 * Explanation: Note that the input contains one empty list. The graph
 * consists of only one node with val = 1 and it does not have any neighbors.
 *
 * Example 3:
 * Input: adjList = []
 * Output: []
 * Explanation: This is an empty graph, it does not have any nodes.
 *
 * Constraints:
 * - The number of nodes in the graph is in the range [0, 100].
 * - 1 <= Node.val <= 100
 * - Node.val is unique for each node.
 * - There are no repeated edges and no self-loops in the graph.
 * - The Graph is connected and all nodes can be visited starting from the
 *   given node.
 */

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <vector>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr; 
        
        unordered_map<Node*, Node*> g; 
        auto dfs = [&g](auto&& self, Node* res, Node* node) -> void {
            for(Node* real : node->neighbors) {
                if(!g.contains(real)) {
                    Node* copy = new Node(real->val); 
                    g[real] = copy;  

                    self(self, copy, real);
                }
                res->neighbors.push_back(g[real]); 
            }  
        };
        
        Node* res = new Node(node->val);
        g[node] = res; 
        dfs(dfs, res, node);

        return res; 
    }
};

// Builds a graph from LeetCode's 1-indexed adjacency list. nodes[0] is node 1.
vector<Node*> build_graph(const vector<vector<int>>& adj_list) {
    vector<Node*> nodes;
    for (int val = 1; val <= (int)adj_list.size(); val++) {
        nodes.push_back(new Node(val));
    }

    for (int i = 0; i < (int)adj_list.size(); i++) {
        for (int neighbor_val : adj_list[i]) {
            nodes[i]->neighbors.push_back(nodes[neighbor_val - 1]);
        }
    }

    return nodes;
}

// Returns every distinct node object reachable from start, compared by address.
vector<Node*> collect_nodes(Node* start) {
    if (start == nullptr) return {};

    unordered_set<Node*> found = {start};
    vector<Node*> stack = {start};

    while (!stack.empty()) {
        Node* node = stack.back();
        stack.pop_back();

        for (Node* neighbor : node->neighbors) {
            if (!found.contains(neighbor)) {
                found.insert(neighbor);
                stack.push_back(neighbor);
            }
        }
    }

    return vector<Node*>(found.begin(), found.end());
}

// Converts a graph back into LeetCode's adjacency-list format.
vector<vector<int>> to_adj_list(Node* start) {
    vector<Node*> nodes = collect_nodes(start);
    sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) { return a->val < b->val; });

    vector<vector<int>> adj_list;
    for (Node* node : nodes) {
        vector<int> neighbor_vals;
        for (Node* neighbor : node->neighbors) {
            neighbor_vals.push_back(neighbor->val);
        }

        adj_list.push_back(neighbor_vals);
    }

    return adj_list;
}

// Clones the graph described by adj_list and checks that the copy is deep and exact.
void assert_clones(const vector<vector<int>>& adj_list) {
    vector<Node*> original_nodes = build_graph(adj_list);
    Node* original = original_nodes.empty() ? nullptr : original_nodes[0];

    Node* clone = Solution().cloneGraph(original);

    // The clone must have the same shape as the input, starting from node 1.
    assert(to_adj_list(clone) == adj_list);

    if (original == nullptr) {
        assert(clone == nullptr);
        return;
    }

    assert(clone->val == 1);

    // A deep copy must not reuse any node object from the original graph.
    unordered_set<Node*> original_set(original_nodes.begin(), original_nodes.end());
    vector<Node*> clone_nodes = collect_nodes(clone);
    for (Node* node : clone_nodes) {
        assert(!original_set.contains(node));
    }

    // Cloning must leave the original graph untouched.
    assert(to_adj_list(original) == adj_list);

    for (Node* node : original_nodes) delete node;
    for (Node* node : clone_nodes) delete node;
}

int main() {
    // Examples from the problem statement.
    assert_clones({{2, 4}, {1, 3}, {2, 4}, {1, 3}});
    assert_clones({{}});
    assert_clones({});

    // Smallest graphs with edges.
    assert_clones({{2}, {1}});
    assert_clones({{2, 3}, {1, 3}, {1, 2}});

    // Neighbor order is not sorted and must be preserved.
    assert_clones({{3, 2}, {1, 3}, {2, 1}});
    assert_clones({{4, 2, 3}, {1}, {1}, {1}});

    // Trees: a path, a star, and a start node that is a leaf.
    assert_clones({{2}, {1, 3}, {2, 4}, {3}});
    assert_clones({{2, 3, 4, 5}, {1}, {1}, {1}, {1}});
    assert_clones({{2}, {1, 3, 4}, {2}, {2}});

    // Cycles mixed with tree branches.
    assert_clones({{2, 3}, {1, 3}, {1, 2, 4}, {3}});
    assert_clones({{2, 3, 4, 5}, {1, 3}, {1, 2}, {1, 5}, {1, 4}});

    // Complete graph on 4 nodes.
    assert_clones({{2, 3, 4}, {1, 3, 4}, {1, 2, 4}, {1, 2, 3}});

    // 100 nodes: the longest path, the longest cycle, and the densest graph.
    {
        const int n = 100;

        vector<vector<int>> path = {{2}};
        vector<vector<int>> cycle = {{n, 2}};
        for (int val = 2; val < n; val++) {
            path.push_back({val - 1, val + 1});
            cycle.push_back({val - 1, val + 1});
        }
        path.push_back({n - 1});
        cycle.push_back({n - 1, 1});

        vector<vector<int>> complete(n);
        for (int val = 1; val <= n; val++) {
            for (int other = 1; other <= n; other++) {
                if (other != val) complete[val - 1].push_back(other);
            }
        }

        assert_clones(path);
        assert_clones(cycle);
        assert_clones(complete);
    }

    return 0;
}
