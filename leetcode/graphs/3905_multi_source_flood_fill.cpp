#include <cassert>
#include <vector>

using namespace std;

// https://leetcode.com/problems/multi-source-flood-fill/
class Solution {
public:
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {
        // TODO: implement
        throw "not implemented";
    }
};

int main() {
    Solution solution;

    {
        vector<vector<int>> sources = {{0, 0, 1000000}};
        vector<vector<int>> expected = {{1000000}};
        assert(solution.colorGrid(1, 1, sources) == expected);
    }

    {
        vector<vector<int>> sources = {{1, 2, 7}};
        vector<vector<int>> expected = {{7, 7, 7, 7}, {7, 7, 7, 7}};
        assert(solution.colorGrid(2, 4, sources) == expected);
    }

    {
        vector<vector<int>> sources = {{0, 0, 2}, {0, 4, 9}};
        vector<vector<int>> expected = {{2, 2, 9, 9, 9}};
        assert(solution.colorGrid(1, 5, sources) == expected);

        sources = {{0, 4, 9}, {0, 0, 2}};
        assert(solution.colorGrid(1, 5, sources) == expected);
    }

    {
        vector<vector<int>> sources = {{0, 0, 9}, {4, 0, 2}};
        vector<vector<int>> expected = {{9}, {9}, {9}, {2}, {2}};
        assert(solution.colorGrid(5, 1, sources) == expected);
    }

    {
        vector<vector<int>> sources = {{0, 0, 4}, {0, 3, 8}, {2, 1, 6}};
        vector<vector<int>> expected = {
            {4, 4, 8, 8},
            {4, 6, 8, 8},
            {6, 6, 6, 8},
        };
        assert(solution.colorGrid(3, 4, sources) == expected);
    }

    {
        vector<vector<int>> sources = {{1, 0, 3}, {1, 4, 8}};
        vector<vector<int>> expected = {
            {3, 3, 8, 8, 8},
            {3, 3, 8, 8, 8},
            {3, 3, 8, 8, 8},
        };
        assert(solution.colorGrid(3, 5, sources) == expected);
    }

    {
        vector<vector<int>> sources = {
            {0, 0, 1}, {0, 1, 1000000}, {1, 0, 5}, {1, 1, 2},
        };
        vector<vector<int>> expected = {{1, 1000000}, {5, 2}};
        assert(solution.colorGrid(2, 2, sources) == expected);
    }

    {
        vector<vector<int>> sources = {{0, 0, 5}, {1, 2, 5}};
        vector<vector<int>> expected = {{5, 5, 5}, {5, 5, 5}};
        assert(solution.colorGrid(2, 3, sources) == expected);
    }

    {
        vector<vector<int>> sources = {{0, 99999, 1}};
        vector<vector<int>> expected(1, vector<int>(100000, 1));
        assert(solution.colorGrid(1, 100000, sources) == expected);
    }

    {
        vector<vector<int>> sources = {{99999, 0, 1}};
        vector<vector<int>> expected(100000, vector<int>(1, 1));
        assert(solution.colorGrid(100000, 1, sources) == expected);
    }

    return 0;
}
