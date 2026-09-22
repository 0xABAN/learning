"""210. Course Schedule II (Medium).

https://leetcode.com/problems/course-schedule-ii/

There are a total of numCourses courses you have to take, labeled from 0 to
numCourses - 1. You are given an array prerequisites where prerequisites[i] =
[a_i, b_i] indicates that you must take course b_i first if you want to take
course a_i.

Return an ordering of courses you should take to finish all courses. If there
are many valid answers, return any of them. If it is impossible to finish all
courses, return an empty array.

Examples:

Example 1:
Input: numCourses = 2, prerequisites = [[1, 0]]
Output: [0, 1]

Example 2:
Input: numCourses = 4, prerequisites = [[1, 0], [2, 0], [3, 1], [3, 2]]
Output: [0, 2, 1, 3]
Explanation: Another valid answer is [0, 1, 2, 3].

Example 3:
Input: numCourses = 1, prerequisites = []
Output: [0]

Constraints:

- 1 <= numCourses <= 2000
- 0 <= prerequisites.length <= 5000
- prerequisites[i].length == 2
- 0 <= a_i, b_i < numCourses
- All the pairs [a_i, b_i] are distinct.
"""


class Solution:
    def findOrder(self, numCourses: int, prerequisites: list[list[int]]) -> list[int]:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    assert solution.findOrder(2, [[1, 0]]) in ([0, 1],)
    assert solution.findOrder(4, [[1, 0], [2, 0], [3, 1], [3, 2]]) in (
        [0, 1, 2, 3],
        [0, 2, 1, 3],
    )
    assert solution.findOrder(1, []) == [0]
    assert solution.findOrder(2, [[1, 0], [0, 1]]) == []


if __name__ == "__main__":
    main()
