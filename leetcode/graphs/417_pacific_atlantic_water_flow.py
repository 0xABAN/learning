"""417. Pacific Atlantic Water Flow (Medium).

https://leetcode.com/problems/pacific-atlantic-water-flow/

There is an m x n rectangular island that borders both the Pacific Ocean and
Atlantic Ocean. The Pacific Ocean touches the island's left and top edges,
and the Atlantic Ocean touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an
m x n integer matrix heights where heights[r][c] represents the height above
sea level of the cell at coordinate (r, c).

The island receives a lot of rain, and the rain water can flow to
neighboring cells directly north, south, east, and west if the neighboring
cell's height is less than or equal to the current cell's height. Water can
flow from any cell adjacent to an ocean into the ocean.

Return a 2D list of grid coordinates result where result[i] = [ri, ci]
denotes that rain water can flow from cell (ri, ci) to both the Pacific and
Atlantic oceans.

Example 1:
Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
Explanation: The following cells can flow to the Pacific and Atlantic
oceans, as shown below:
[0,4]: [0,4] -> Pacific Ocean
       [0,4] -> Atlantic Ocean
[1,3]: [1,3] -> [0,3] -> Pacific Ocean
       [1,3] -> [1,4] -> Atlantic Ocean
[1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean
       [1,4] -> Atlantic Ocean
[2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean
       [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
[3,0]: [3,0] -> Pacific Ocean
       [3,0] -> [4,0] -> Atlantic Ocean
[3,1]: [3,1] -> [3,0] -> Pacific Ocean
       [3,1] -> [4,1] -> Atlantic Ocean
[4,0]: [4,0] -> Pacific Ocean
       [4,0] -> Atlantic Ocean
Note that there are other possible paths for these cells to flow to the
Pacific and Atlantic oceans.

Example 2:
Input: heights = [[1]]
Output: [[0,0]]
Explanation: The water can flow from the only cell to the Pacific and
Atlantic oceans.

Constraints:
- m == heights.length
- n == heights[r].length
- 1 <= m, n <= 200
- 0 <= heights[r][c] <= 10^5
"""


class Solution:
    def pacificAtlantic(self, heights: list[list[int]]) -> list[list[int]]:
        """
        use dfs on pacific, then atlantic, and take their intersection 
        """

        m, n = len(heights), len(heights[0])     
        nav = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        ans = []
        
        pac = set()
        atl = set() 
        
        def dfs(r, c, ocean): 
            if (r, c) in ocean: 
                return
            
            ocean.add((r, c))
            for dr, dc in nav: 
                nr, nc = r+dr, c+dc 
                
                if (0 <= nr < m and 0 <= nc < n) and (heights[nr][nc] >= heights[r][c]): 
                    dfs(nr, nc, ocean)

                    
        for c in range(n): 
            dfs(0, c, pac)
        
        for r in range(m): 
            dfs(r, 0, pac)

        for c in range(n): 
            dfs(m-1, c, atl)
        
        for r in range(m): 
            dfs(r, n-1, atl)
        
        for r in range(m): 
            for c in range(n): 
                if (r, c) in pac and (r, c) in atl: 
                    ans.append([r, c])

        return ans




        
def main() -> None:
    solution = Solution()

    # The answer may be returned in any order, so tests compare sorted results.
    def check(heights: list[list[int]], expected: list[list[int]]) -> None:
        assert sorted(solution.pacificAtlantic(heights)) == expected

    # Examples from the problem statement.
    check(
        [
            [1, 2, 2, 3, 5],
            [3, 2, 3, 4, 4],
            [2, 4, 5, 3, 1],
            [6, 7, 1, 4, 5],
            [5, 1, 1, 2, 4],
        ],
        [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]],
    )
    check([[1]], [[0, 0]])

    # A single row or column touches both oceans everywhere.
    check([[1, 2, 3]], [[0, 0], [0, 1], [0, 2]])
    check([[3], [1], [5]], [[0, 0], [1, 0], [2, 0]])

    # Water flows between cells of equal height.
    check([[1, 1], [1, 1]], [[0, 0], [0, 1], [1, 0], [1, 1]])

    # A peak drains everywhere, but a pit cannot drain at all.
    check(
        [[1, 1, 1], [1, 5, 1], [1, 1, 1]],
        [[0, 0], [0, 1], [0, 2], [1, 0], [1, 1], [1, 2], [2, 0], [2, 1], [2, 2]],
    )
    check(
        [[5, 5, 5], [5, 1, 5], [5, 5, 5]],
        [[0, 0], [0, 1], [0, 2], [1, 0], [1, 2], [2, 0], [2, 1], [2, 2]],
    )

    # Land rising toward one ocean only lets the cells on that ocean's edges qualify.
    check([[1, 2, 3], [2, 3, 4], [3, 4, 5]], [[0, 2], [1, 2], [2, 0], [2, 1], [2, 2]])
    check([[5, 4, 3], [4, 3, 2], [3, 2, 1]], [[0, 0], [0, 1], [0, 2], [1, 0], [2, 0]])

    # Non-square grid where the top row is cut off from the Atlantic.
    check([[1, 2, 3, 4], [8, 7, 6, 5]], [[0, 3], [1, 0], [1, 1], [1, 2], [1, 3]])

    # Maximum-height walls trap a corner against a single ocean.
    check(
        [[0, 0, 0], [0, 0, 100000], [0, 100000, 0]],
        [[0, 0], [0, 1], [0, 2], [1, 0], [1, 1], [1, 2], [2, 0], [2, 1]],
    )
    check(
        [[0, 100000, 0], [100000, 0, 0], [0, 0, 0]],
        [[0, 1], [0, 2], [1, 0], [1, 1], [1, 2], [2, 0], [2, 1], [2, 2]],
    )

    n = 200

    # 200 x 200 flat grid: every cell qualifies.
    check(
        [[0] * n for _ in range(n)],
        [[r, c] for r in range(n) for c in range(n)],
    )

    # 200 x 200 grid rising toward the bottom-right: only the Atlantic edges qualify.
    check(
        [[r + c for c in range(n)] for r in range(n)],
        [[r, n - 1] for r in range(n - 1)] + [[n - 1, c] for c in range(n)],
    )


if __name__ == "__main__":
    main()
