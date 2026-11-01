#include <cassert>
#include <vector>

using namespace std;

// https://leetcode.com/problems/minimum-cost-path-with-even-xor-parity/
class Solution {
public:
    int minActivationCost(vector<vector<int>>& edges, vector<int>& values) {
        // TODO: implement
        throw "not implemented";
    }
};

int main() {
    Solution solution;

    {
        vector<vector<int>> edges = {{0, 1, 4}, {0, 2, 6}, {0, 3, 3}, {3, 4, 5}};
        vector<int> values = {3, 1, 7, 1, 3};
        assert(solution.minActivationCost(edges, values) == 7);
    }

    {
        vector<vector<int>> edges = {{0, 1, 5}, {1, 2, 10}};
        vector<int> values = {1, 7, 3};
        assert(solution.minActivationCost(edges, values) == 5);
    }

    {
        vector<vector<int>> edges = {{0, 1, 5}, {0, 2, 7}, {0, 3, 9}};
        vector<int> values = {1, 3, 5, 9};
        assert(solution.minActivationCost(edges, values) == -1);
    }

    return 0;
}
