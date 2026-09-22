"""2577. Minimum Time to Visit a Cell In a Grid (Hard).

https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/

You are given an m x n matrix grid of non-negative integers. grid[row][col]
is the minimum time at which you may visit cell (row, col): your arrival
must be at or after that time.

You start at the top-left cell at time 0. You must move to an adjacent cell
in one of four directions: up, down, left, or right. Each move takes one
second.

Return the minimum time at which you can visit the bottom-right cell.
If you cannot visit it, return -1.

Example 1:
Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
Output: 7
Explanation: One valid path, listing positions at times 0 through 7, is
(0,0), (0,1), (1,1), (1,2), (1,1), (1,2), (1,3), (2,3).
Each arrival meets the cell's minimum time. No earlier arrival is possible.

Example 2:
Input: grid = [[0,2,4],[3,2,1],[1,0,4]]
Output: -1
Explanation: There is no path from the top-left to the bottom-right cell.

Constraints:
- m == len(grid)
- n == len(grid[i])
- 2 <= m, n <= 1000
- 4 <= m * n <= 100000
- 0 <= grid[i][j] <= 100000
- grid[0][0] == 0
"""


class Solution:
    def minimumTime(self, grid: list[list[int]]) -> int:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    assert solution.minimumTime([[0, 0], [0, 0]]) == 2
    assert solution.minimumTime([[0, 2], [2, 0]]) == -1
    assert solution.minimumTime([[0, 1], [2, 3]]) == 4
    assert solution.minimumTime([[0, 2], [1, 4]]) == 4

    assert solution.minimumTime([[0, 1, 0], [0, 0, 4]]) == 5
    assert solution.minimumTime([[0, 1], [9, 2], [0, 3]]) == 3
    assert solution.minimumTime([[0, 1, 100], [1, 2, 100], [2, 3, 4]]) == 4
    assert solution.minimumTime([[0, 1, 9], [9, 9, 9], [9, 9, 0]]) == 12

    assert solution.minimumTime([[0, 0], [0, 100000]]) == 100000
    assert solution.minimumTime([[0, 0, 0], [0, 0, 100000]]) == 100001
    assert solution.minimumTime([[0] * 1000 for _ in range(100)]) == 1098


if __name__ == "__main__":
    main()
