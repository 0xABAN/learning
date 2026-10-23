/*
 * 311. Sparse Matrix Multiplication (Medium)
 *
 * https://leetcode.com/problems/sparse-matrix-multiplication/
 *
 * Given two sparse matrices mat1 of size m x k and mat2 of size k x n,
 * return the result of mat1 x mat2. You may assume that multiplication is
 * always possible.
 *
 * Example 1:
 * Input: mat1 = [[1,0,0],[-1,0,3]], mat2 = [[7,0,0],[0,0,0],[0,0,1]]
 * Output: [[7,0,0],[-7,0,3]]
 *
 * Example 2:
 * Input: mat1 = [[0]], mat2 = [[0]]
 * Output: [[0]]
 *
 * Constraints:
 * - m == mat1.length
 * - k == mat1[i].length == mat2.length
 * - n == mat2[i].length
 * - 1 <= m, n, k <= 100
 * - -100 <= mat1[i][j], mat2[i][j] <= 100
 */

#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        // TODO: implement
        throw "not implemented";
    }
};

int main() {
    Solution solution;

    // Examples from the problem statement.
    {
        vector<vector<int>> mat1 = {{1, 0, 0}, {-1, 0, 3}};
        vector<vector<int>> mat2 = {{7, 0, 0}, {0, 0, 0}, {0, 0, 1}};
        vector<vector<int>> expected = {{7, 0, 0}, {-7, 0, 3}};
        assert(solution.multiply(mat1, mat2) == expected);
    }

    {
        vector<vector<int>> mat1 = {{0}};
        vector<vector<int>> mat2 = {{0}};
        vector<vector<int>> expected = {{0}};
        assert(solution.multiply(mat1, mat2) == expected);
    }

    // 1 x 1 matrices with a negative entry.
    {
        vector<vector<int>> mat1 = {{-3}};
        vector<vector<int>> mat2 = {{4}};
        vector<vector<int>> expected = {{-12}};
        assert(solution.multiply(mat1, mat2) == expected);
    }

    // A row times a column gives a single entry.
    {
        vector<vector<int>> mat1 = {{1, 2, 3}};
        vector<vector<int>> mat2 = {{4}, {5}, {6}};
        vector<vector<int>> expected = {{32}};
        assert(solution.multiply(mat1, mat2) == expected);
    }

    // A column times a row gives a full matrix.
    {
        vector<vector<int>> mat1 = {{1}, {-2}, {3}};
        vector<vector<int>> mat2 = {{4, 5}};
        vector<vector<int>> expected = {{4, 5}, {-8, -10}, {12, 15}};
        assert(solution.multiply(mat1, mat2) == expected);
    }

    // Dense non-square matrices: 2 x 3 times 3 x 2.
    {
        vector<vector<int>> mat1 = {{1, 2, 3}, {4, 5, 6}};
        vector<vector<int>> mat2 = {{7, 8}, {9, 10}, {11, 12}};
        vector<vector<int>> expected = {{58, 64}, {139, 154}};
        assert(solution.multiply(mat1, mat2) == expected);
    }

    // The result has mat1's row count and mat2's column count: 2 x 1 times 1 x 4.
    {
        vector<vector<int>> mat1 = {{2}, {0}};
        vector<vector<int>> mat2 = {{1, -1, 0, 3}};
        vector<vector<int>> expected = {{2, -2, 0, 6}, {0, 0, 0, 0}};
        assert(solution.multiply(mat1, mat2) == expected);
    }

    // Multiplying by the identity leaves the other matrix unchanged.
    {
        vector<vector<int>> identity = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        vector<vector<int>> other = {{5, -6, 0}, {0, 7, 8}, {-9, 0, 100}};
        assert(solution.multiply(identity, other) == other);
        assert(solution.multiply(other, identity) == other);
    }

    // Operand order matters.
    {
        vector<vector<int>> a = {{0, 1}, {0, 0}};
        vector<vector<int>> b = {{0, 0}, {1, 0}};
        vector<vector<int>> ab = {{1, 0}, {0, 0}};
        vector<vector<int>> ba = {{0, 0}, {0, 1}};
        assert(solution.multiply(a, b) == ab);
        assert(solution.multiply(b, a) == ba);
    }

    // Nonzero entries can cancel out to a zero result.
    {
        vector<vector<int>> mat1 = {{1, -1}, {2, -2}};
        vector<vector<int>> mat2 = {{3, 4}, {3, 4}};
        vector<vector<int>> expected = {{0, 0}, {0, 0}};
        assert(solution.multiply(mat1, mat2) == expected);
    }

    // A zero matrix still produces a result of the right shape.
    {
        vector<vector<int>> mat1 = {{0, 0, 0}, {0, 0, 0}};
        vector<vector<int>> mat2 = {{1, 2}, {3, 4}, {5, 6}};
        vector<vector<int>> expected = {{0, 0}, {0, 0}};
        assert(solution.multiply(mat1, mat2) == expected);
    }

    const int n = 100;

    // 100 x 100 dense matrices at the value limits: every entry is 100 * 100 * (+/-100).
    {
        vector<vector<int>> mat1(n, vector<int>(n, 100));
        vector<vector<int>> mat2(n, vector<int>(n, -100));
        vector<vector<int>> expected(n, vector<int>(n, -1000000));
        assert(solution.multiply(mat1, mat2) == expected);
    }

    // 100 x 100 sparse matrices: a scaled diagonal times a single nonzero entry.
    {
        vector<vector<int>> mat1(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            mat1[i][i] = 2;
        }

        vector<vector<int>> mat2(n, vector<int>(n, 0));
        mat2[37][59] = -100;

        vector<vector<int>> expected(n, vector<int>(n, 0));
        expected[37][59] = -200;

        assert(solution.multiply(mat1, mat2) == expected);
    }

    // Longest inner dimension: 1 x 100 times 100 x 1.
    {
        vector<vector<int>> mat1 = {vector<int>(n, -100)};
        vector<vector<int>> mat2(n, vector<int>(1, -100));
        vector<vector<int>> expected = {{1000000}};
        assert(solution.multiply(mat1, mat2) == expected);
    }

    // Shortest inner dimension with the largest result: 100 x 1 times 1 x 100.
    {
        vector<vector<int>> mat1(n);
        for (int i = 0; i < n; i++) {
            mat1[i] = {i - 50};
        }

        vector<vector<int>> mat2 = {vector<int>(n)};
        for (int j = 0; j < n; j++) {
            mat2[0][j] = j % 2 == 0 ? 1 : -1;
        }

        vector<vector<int>> expected(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                expected[i][j] = j % 2 == 0 ? i - 50 : 50 - i;
            }
        }

        assert(solution.multiply(mat1, mat2) == expected);
    }

    return 0;
}
