#include <cassert>
#include <vector>

using namespace std;

// https://leetcode.com/problems/is-graph-bipartite/
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        // TODO: implement
        throw "not implemented";
    }
};

int main() {
    Solution solution;

    {
        vector<vector<int>> graph = {{}};
        assert(solution.isBipartite(graph) == true);
    }

    {
        vector<vector<int>> graph(100);
        assert(solution.isBipartite(graph) == true);
    }

    {
        vector<vector<int>> graph = {{1}, {0}};
        assert(solution.isBipartite(graph) == true);
    }

    {
        vector<vector<int>> graph = {{1, 2, 3, 4}, {0}, {0}, {0}, {0}};
        assert(solution.isBipartite(graph) == true);
    }

    {
        vector<vector<int>> graph = {{1, 4}, {0, 2}, {1, 3}, {2, 4}, {0, 3}};
        assert(solution.isBipartite(graph) == false);
    }

    {
        vector<vector<int>> graph = {
            {1, 5}, {0, 2}, {1, 3}, {2, 4}, {3, 5}, {0, 4},
        };
        assert(solution.isBipartite(graph) == true);
    }

    {
        vector<vector<int>> graph = {
            {}, {2}, {1}, {4, 5}, {3, 5}, {3, 4}, {},
        };
        assert(solution.isBipartite(graph) == false);
    }

    {
        vector<vector<int>> graph = {{2}, {}, {0, 4}, {5}, {2}, {3}};
        assert(solution.isBipartite(graph) == true);
    }

    {
        vector<vector<int>> graph = {
            {3, 4, 5}, {3, 4, 5}, {3, 4, 5},
            {0, 1, 2}, {0, 1, 2}, {0, 1, 2},
        };
        assert(solution.isBipartite(graph) == true);
    }

    return 0;
}
