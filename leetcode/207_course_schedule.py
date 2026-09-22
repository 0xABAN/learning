"""207. Course Schedule (Medium).

https://leetcode.com/problems/course-schedule/
"""

from collections import defaultdict, deque


class Solution:
    def canFinish(self, numCourses: int, prerequisites: list[list[int]]) -> bool:
        """
        BFS topological-sort solution.

        Count each node's incoming edges and process nodes with no
        prerequisites first.

        [1, 0]

        0 -> 1: 0 is a prerequisite for 1

        [0, 1]
        """

        graph = defaultdict(list)
        in_edges = [0] * numCourses

        for u, v in prerequisites:
            graph[v].append(u)
            in_edges[u] += 1

        queue = deque()
        for node in range(numCourses):
            if in_edges[node] == 0:
                queue.append(node)

        while queue:
            node = queue.popleft()

            for neighbor in graph[node]:
                in_edges[neighbor] -= 1

                if in_edges[neighbor] == 0:
                    queue.append(neighbor)

        return all(edge == 0 for edge in in_edges)

def main() -> None:
    solution = Solution()

    assert solution.canFinish(1, []) is True
    assert solution.canFinish(2, [[1, 0]]) is True
    assert solution.canFinish(3, [[1, 0], [1, 2], [2, 0]]) is True
    assert solution.canFinish(3, [[0, 1], [1, 2], [2, 0]]) is False
    assert solution.canFinish(4, [[1, 0], [3, 3]]) is False

if __name__ == "__main__":
    main()
