/*
 * 399. Evaluate Division (Medium)
 *
 * https://leetcode.com/problems/evaluate-division/
 *
 * You are given an array of variable pairs equations and an array of real
 * numbers values, where equations[i] = [Ai, Bi] and values[i] represent the
 * equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a
 * single variable.
 *
 * You are also given some queries, where queries[j] = [Cj, Dj] represents
 * the jth query where you must find the answer for Cj / Dj = ?.
 *
 * Return the answers to all queries. If a single answer cannot be
 * determined, return -1.0.
 *
 * Note: The input is always valid. You may assume that evaluating the
 * queries will not result in division by zero and that there is no
 * contradiction.
 *
 * Note: The variables that do not occur in the list of equations are
 * undefined, so the answer cannot be determined for them.
 *
 * Example 1:
 * Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0],
 *        queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
 * Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
 * Explanation:
 * Given: a / b = 2.0, b / c = 3.0
 * queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
 * return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
 * note: x is undefined => -1.0
 *
 * Example 2:
 * Input: equations = [["a","b"],["b","c"],["bc","cd"]],
 *        values = [1.5,2.5,5.0],
 *        queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
 * Output: [3.75000,0.40000,5.00000,0.20000]
 *
 * Example 3:
 * Input: equations = [["a","b"]], values = [0.5],
 *        queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
 * Output: [0.50000,2.00000,-1.00000,-1.00000]
 *
 * Constraints:
 * - 1 <= equations.length <= 20
 * - equations[i].length == 2
 * - 1 <= Ai.length, Bi.length <= 5
 * - values.length == equations.length
 * - 0.0 < values[i] <= 20.0
 * - 1 <= queries.length <= 20
 * - queries[i].length == 2
 * - 1 <= Cj.length, Dj.length <= 5
 * - Ai, Bi, Cj, Dj consist of lower case English letters and digits.
 */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // TODO: implement
        throw "not implemented";
    }
};

// Answers are floating point, so each one is compared within a small relative tolerance.
bool close(const vector<double>& actual, const vector<double>& expected) {
    if (actual.size() != expected.size()) return false;

    for (size_t i = 0; i < actual.size(); i++) {
        if (abs(actual[i] - expected[i]) > 1e-9 * max(1.0, abs(expected[i]))) return false;
    }

    return true;
}

int main() {
    Solution solution;

    // Examples from the problem statement.
    {
        vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}};
        vector<double> values = {2.0, 3.0};
        vector<vector<string>> queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
        assert(close(solution.calcEquation(equations, values, queries), {6.0, 0.5, -1.0, 1.0, -1.0}));
    }

    {
        vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
        vector<double> values = {1.5, 2.5, 5.0};
        vector<vector<string>> queries = {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
        assert(close(solution.calcEquation(equations, values, queries), {3.75, 0.4, 5.0, 0.2}));
    }

    {
        vector<vector<string>> equations = {{"a", "b"}};
        vector<double> values = {0.5};
        vector<vector<string>> queries = {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}};
        assert(close(solution.calcEquation(equations, values, queries), {0.5, 2.0, -1.0, -1.0}));
    }

    // A variable that only ever appears as a denominator is still defined.
    {
        vector<vector<string>> equations = {{"a", "b"}};
        vector<double> values = {4.0};
        vector<vector<string>> queries = {{"b", "b"}, {"b", "a"}};
        assert(close(solution.calcEquation(equations, values, queries), {1.0, 0.25}));
    }

    // Variables in different components cannot be compared.
    {
        vector<vector<string>> equations = {{"a", "b"}, {"c", "d"}};
        vector<double> values = {2.0, 3.0};
        vector<vector<string>> queries = {{"a", "d"}, {"c", "b"}, {"a", "b"}, {"d", "c"}};
        assert(close(solution.calcEquation(equations, values, queries), {-1.0, -1.0, 2.0, 1.0 / 3.0}));
    }

    // Fractional values multiply along the path.
    {
        vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}};
        vector<double> values = {0.5, 0.25};
        vector<vector<string>> queries = {{"a", "c"}, {"c", "a"}};
        assert(close(solution.calcEquation(equations, values, queries), {0.125, 8.0}));
    }

    // Consistent equations that form a cycle.
    {
        vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}, {"c", "a"}};
        vector<double> values = {2.0, 3.0, 1.0 / 6.0};
        vector<vector<string>> queries = {{"a", "c"}, {"c", "b"}, {"b", "a"}, {"a", "a"}};
        assert(close(solution.calcEquation(equations, values, queries), {6.0, 1.0 / 3.0, 0.5, 1.0}));
    }

    // Two leaves are related only through the hub they share.
    {
        vector<vector<string>> equations = {{"h", "p"}, {"h", "q"}, {"h", "r"}};
        vector<double> values = {2.0, 5.0, 10.0};
        vector<vector<string>> queries = {{"p", "q"}, {"r", "p"}, {"q", "r"}};
        assert(close(solution.calcEquation(equations, values, queries), {2.5, 0.2, 2.0}));
    }

    // Five-character names that mix letters and digits.
    {
        vector<vector<string>> equations = {{"abc12", "x9"}, {"x9", "zz"}};
        vector<double> values = {4.5, 2.0};
        vector<vector<string>> queries = {{"abc12", "zz"}, {"zz", "abc12"}, {"abc12", "abc1"}};
        assert(close(solution.calcEquation(equations, values, queries), {9.0, 1.0 / 9.0, -1.0}));
    }

    // The longest chain: 20 equations x0 / x1 = ... = x19 / x20 = 2.
    {
        vector<vector<string>> equations;
        vector<double> values;
        for (int i = 0; i < 20; i++) {
            equations.push_back({"x" + to_string(i), "x" + to_string(i + 1)});
            values.push_back(2.0);
        }

        vector<vector<string>> queries = {
            {"x0", "x20"}, {"x20", "x0"}, {"x5", "x15"}, {"x15", "x5"}, {"x10", "x10"}, {"x0", "x21"},
        };
        vector<double> expected = {1048576.0, 1.0 / 1048576.0, 1024.0, 1.0 / 1024.0, 1.0, -1.0};
        assert(close(solution.calcEquation(equations, values, queries), expected));
    }

    // 20 queries against the maximum value of 20.0.
    {
        vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}};
        vector<double> values = {20.0, 20.0};

        vector<vector<string>> queries;
        vector<double> expected;
        for (int i = 0; i < 4; i++) {
            queries.insert(queries.end(), {{"a", "b"}, {"b", "c"}, {"a", "c"}, {"c", "a"}, {"c", "d"}});
            expected.insert(expected.end(), {20.0, 20.0, 400.0, 1.0 / 400.0, -1.0});
        }

        assert(close(solution.calcEquation(equations, values, queries), expected));
    }

    return 0;
}
