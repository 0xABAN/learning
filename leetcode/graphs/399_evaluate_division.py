"""399. Evaluate Division (Medium).

https://leetcode.com/problems/evaluate-division/

You are given an array of variable pairs equations and an array of real
numbers values, where equations[i] = [Ai, Bi] and values[i] represent the
equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a
single variable.

You are also given some queries, where queries[j] = [Cj, Dj] represents the
jth query where you must find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined,
return -1.0.

Note: The input is always valid. You may assume that evaluating the queries
will not result in division by zero and that there is no contradiction.

Note: The variables that do not occur in the list of equations are
undefined, so the answer cannot be determined for them.

Example 1:
Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0],
       queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation:
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
note: x is undefined => -1.0

Example 2:
Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
       queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]

Example 3:
Input: equations = [["a","b"]], values = [0.5],
       queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]

Constraints:
- 1 <= equations.length <= 20
- equations[i].length == 2
- 1 <= Ai.length, Bi.length <= 5
- values.length == equations.length
- 0.0 < values[i] <= 20.0
- 1 <= queries.length <= 20
- queries[i].length == 2
- 1 <= Cj.length, Dj.length <= 5
- Ai, Bi, Cj, Dj consist of lower case English letters and digits.
"""

import math


class Solution:
    def calcEquation(
        self, equations: list[list[str]], values: list[float], queries: list[list[str]]
    ) -> list[float]:
        raise NotImplementedError


def close(actual: list[float], expected: list[float]) -> bool:
    """Answers are floating point, so each one is compared within a small relative tolerance."""
    return len(actual) == len(expected) and all(
        math.isclose(a, e, rel_tol=1e-9, abs_tol=1e-9) for a, e in zip(actual, expected)
    )


def main() -> None:
    solution = Solution()

    # Examples from the problem statement.
    assert close(
        solution.calcEquation(
            [["a", "b"], ["b", "c"]],
            [2.0, 3.0],
            [["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"]],
        ),
        [6.0, 0.5, -1.0, 1.0, -1.0],
    )
    assert close(
        solution.calcEquation(
            [["a", "b"], ["b", "c"], ["bc", "cd"]],
            [1.5, 2.5, 5.0],
            [["a", "c"], ["c", "b"], ["bc", "cd"], ["cd", "bc"]],
        ),
        [3.75, 0.4, 5.0, 0.2],
    )
    assert close(
        solution.calcEquation(
            [["a", "b"]],
            [0.5],
            [["a", "b"], ["b", "a"], ["a", "c"], ["x", "y"]],
        ),
        [0.5, 2.0, -1.0, -1.0],
    )

    # A variable that only ever appears as a denominator is still defined.
    assert close(
        solution.calcEquation([["a", "b"]], [4.0], [["b", "b"], ["b", "a"]]),
        [1.0, 0.25],
    )

    # Variables in different components cannot be compared.
    assert close(
        solution.calcEquation(
            [["a", "b"], ["c", "d"]],
            [2.0, 3.0],
            [["a", "d"], ["c", "b"], ["a", "b"], ["d", "c"]],
        ),
        [-1.0, -1.0, 2.0, 1 / 3],
    )

    # Fractional values multiply along the path.
    assert close(
        solution.calcEquation([["a", "b"], ["b", "c"]], [0.5, 0.25], [["a", "c"], ["c", "a"]]),
        [0.125, 8.0],
    )

    # Consistent equations that form a cycle.
    assert close(
        solution.calcEquation(
            [["a", "b"], ["b", "c"], ["c", "a"]],
            [2.0, 3.0, 1 / 6],
            [["a", "c"], ["c", "b"], ["b", "a"], ["a", "a"]],
        ),
        [6.0, 1 / 3, 0.5, 1.0],
    )

    # Two leaves are related only through the hub they share.
    assert close(
        solution.calcEquation(
            [["h", "p"], ["h", "q"], ["h", "r"]],
            [2.0, 5.0, 10.0],
            [["p", "q"], ["r", "p"], ["q", "r"]],
        ),
        [2.5, 0.2, 2.0],
    )

    # Five-character names that mix letters and digits.
    assert close(
        solution.calcEquation(
            [["abc12", "x9"], ["x9", "zz"]],
            [4.5, 2.0],
            [["abc12", "zz"], ["zz", "abc12"], ["abc12", "abc1"]],
        ),
        [9.0, 1 / 9, -1.0],
    )

    # The longest chain: 20 equations x0 / x1 = ... = x19 / x20 = 2.
    equations = [[f"x{i}", f"x{i + 1}"] for i in range(20)]
    values = [2.0] * 20
    queries = [["x0", "x20"], ["x20", "x0"], ["x5", "x15"], ["x15", "x5"], ["x10", "x10"], ["x0", "x21"]]
    assert close(
        solution.calcEquation(equations, values, queries),
        [2.0**20, 2.0**-20, 1024.0, 1 / 1024, 1.0, -1.0],
    )

    # 20 queries against the maximum value of 20.0.
    queries = [["a", "b"], ["b", "c"], ["a", "c"], ["c", "a"], ["c", "d"]] * 4
    expected = [20.0, 20.0, 400.0, 1 / 400, -1.0] * 4
    assert close(solution.calcEquation([["a", "b"], ["b", "c"]], [20.0, 20.0], queries), expected)


if __name__ == "__main__":
    main()
