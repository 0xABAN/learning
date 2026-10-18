/*
 * 417. Pacific Atlantic Water Flow (Medium)
 *
 * https://leetcode.com/problems/pacific-atlantic-water-flow/
 *
 * There is an m x n rectangular island that borders both the Pacific Ocean
 * and Atlantic Ocean. The Pacific Ocean touches the island's left and top
 * edges, and the Atlantic Ocean touches the island's right and bottom edges.
 *
 * The island is partitioned into a grid of square cells. You are given an
 * m x n integer matrix heights where heights[r][c] represents the height
 * above sea level of the cell at coordinate (r, c).
 *
 * The island receives a lot of rain, and the rain water can flow to
 * neighboring cells directly north, south, east, and west if the neighboring
 * cell's height is less than or equal to the current cell's height. Water
 * can flow from any cell adjacent to an ocean into the ocean.
 *
 * Return a 2D list of grid coordinates result where result[i] = [ri, ci]
 * denotes that rain water can flow from cell (ri, ci) to both the Pacific
 * and Atlantic oceans.
 *
 * Example 1:
 * Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
 * Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
 * Explanation: The following cells can flow to the Pacific and Atlantic
 * oceans, as shown below:
 * [0,4]: [0,4] -> Pacific Ocean
 *        [0,4] -> Atlantic Ocean
 * [1,3]: [1,3] -> [0,3] -> Pacific Ocean
 *        [1,3] -> [1,4] -> Atlantic Ocean
 * [1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean
 *        [1,4] -> Atlantic Ocean
 * [2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean
 *        [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
 * [3,0]: [3,0] -> Pacific Ocean
 *        [3,0] -> [4,0] -> Atlantic Ocean
 * [3,1]: [3,1] -> [3,0] -> Pacific Ocean
 *        [3,1] -> [4,1] -> Atlantic Ocean
 * [4,0]: [4,0] -> Pacific Ocean
 *        [4,0] -> Atlantic Ocean
 * Note that there are other possible paths for these cells to flow to the
 * Pacific and Atlantic oceans.
 *
 * Example 2:
 * Input: heights = [[1]]
 * Output: [[0,0]]
 * Explanation: The water can flow from the only cell to the Pacific and
 * Atlantic oceans.
 *
 * Constraints:
 * - m == heights.length
 * - n == heights[r].length
 * - 1 <= m, n <= 200
 * - 0 <= heights[r][c] <= 10^5
 */

#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // TODO: implement
        throw "not implemented";
    }
};

// The answer may be returned in any order, so tests compare sorted results.
vector<vector<int>> sorted(vector<vector<int>> cells) {
    sort(cells.begin(), cells.end());
    return cells;
}

int main() {
    Solution solution;

    // Examples from the problem statement.
    {
        vector<vector<int>> heights = {
            {1, 2, 2, 3, 5},
            {3, 2, 3, 4, 4},
            {2, 4, 5, 3, 1},
            {6, 7, 1, 4, 5},
            {5, 1, 1, 2, 4},
        };
        vector<vector<int>> expected = {{0, 4}, {1, 3}, {1, 4}, {2, 2}, {3, 0}, {3, 1}, {4, 0}};
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    {
        vector<vector<int>> heights = {{1}};
        vector<vector<int>> expected = {{0, 0}};
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    // A single row or column touches both oceans everywhere.
    {
        vector<vector<int>> heights = {{1, 2, 3}};
        vector<vector<int>> expected = {{0, 0}, {0, 1}, {0, 2}};
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    {
        vector<vector<int>> heights = {{3}, {1}, {5}};
        vector<vector<int>> expected = {{0, 0}, {1, 0}, {2, 0}};
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    // Water flows between cells of equal height.
    {
        vector<vector<int>> heights = {{1, 1}, {1, 1}};
        vector<vector<int>> expected = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    // A peak drains everywhere, but a pit cannot drain at all.
    {
        vector<vector<int>> heights = {{1, 1, 1}, {1, 5, 1}, {1, 1, 1}};
        vector<vector<int>> expected = {
            {0, 0}, {0, 1}, {0, 2},
            {1, 0}, {1, 1}, {1, 2},
            {2, 0}, {2, 1}, {2, 2},
        };
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    {
        vector<vector<int>> heights = {{5, 5, 5}, {5, 1, 5}, {5, 5, 5}};
        vector<vector<int>> expected = {
            {0, 0}, {0, 1}, {0, 2},
            {1, 0}, {1, 2},
            {2, 0}, {2, 1}, {2, 2},
        };
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    // Land rising toward one ocean only lets the cells on that ocean's edges qualify.
    {
        vector<vector<int>> heights = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
        vector<vector<int>> expected = {{0, 2}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    {
        vector<vector<int>> heights = {{5, 4, 3}, {4, 3, 2}, {3, 2, 1}};
        vector<vector<int>> expected = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {2, 0}};
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    // Non-square grid where the top row is cut off from the Atlantic.
    {
        vector<vector<int>> heights = {{1, 2, 3, 4}, {8, 7, 6, 5}};
        vector<vector<int>> expected = {{0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}};
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    // Maximum-height walls trap a corner against a single ocean.
    {
        vector<vector<int>> heights = {{0, 0, 0}, {0, 0, 100000}, {0, 100000, 0}};
        vector<vector<int>> expected = {
            {0, 0}, {0, 1}, {0, 2},
            {1, 0}, {1, 1}, {1, 2},
            {2, 0}, {2, 1},
        };
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    {
        vector<vector<int>> heights = {{0, 100000, 0}, {100000, 0, 0}, {0, 0, 0}};
        vector<vector<int>> expected = {
            {0, 1}, {0, 2},
            {1, 0}, {1, 1}, {1, 2},
            {2, 0}, {2, 1}, {2, 2},
        };
        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    // 200 x 200 flat grid: every cell qualifies.
    {
        const int n = 200;
        vector<vector<int>> heights(n, vector<int>(n, 0));

        vector<vector<int>> expected;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                expected.push_back({r, c});
            }
        }

        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    // 200 x 200 grid rising toward the bottom-right: only the Atlantic edges qualify.
    {
        const int n = 200;
        vector<vector<int>> heights(n, vector<int>(n));
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                heights[r][c] = r + c;
            }
        }

        vector<vector<int>> expected;
        for (int r = 0; r < n - 1; r++) {
            expected.push_back({r, n - 1});
        }
        for (int c = 0; c < n; c++) {
            expected.push_back({n - 1, c});
        }

        assert(sorted(solution.pacificAtlantic(heights)) == expected);
    }

    return 0;
}
