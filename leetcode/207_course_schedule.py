"""207. Course Schedule (Medium).

https://leetcode.com/problems/course-schedule/
"""


class Solution:
    def canFinish(self, numCourses: int, prerequisites: list[list[int]]) -> bool:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    assert solution.canFinish(1, []) is True
    assert solution.canFinish(2000, []) is True
    assert solution.canFinish(1, [[0, 0]]) is False

    assert solution.canFinish(5, [[4, 3], [3, 2], [2, 1], [1, 0]]) is True
    assert solution.canFinish(4, [[1, 0], [2, 0], [3, 1], [3, 2]]) is True
    assert solution.canFinish(7, [[1, 0], [3, 2], [5, 4]]) is True

    assert solution.canFinish(3, [[0, 1], [1, 2], [2, 0]]) is False
    assert solution.canFinish(6, [[1, 0], [2, 1], [0, 2], [4, 3]]) is False
    assert solution.canFinish(4, [[1, 0], [3, 3]]) is False
    assert solution.canFinish(4, [[1, 0], [2, 0], [3, 1], [3, 2], [0, 3]]) is False


if __name__ == "__main__":
    main()
