"""992. Subarrays with K Different Integers (Hard).

https://leetcode.com/problems/subarrays-with-k-different-integers/

Given an integer array nums and an integer k, return the number of good
subarrays of nums.

A good array is an array where the number of different integers in that array
is exactly k.
- For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.

A subarray is a contiguous part of an array.

Examples:
- nums = [1,2,1,2,3], k = 2 -> 7
  Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2],
  [2,3], [1,2,1], [2,1,2], [1,2,1,2]
- nums = [1,2,1,3,4], k = 3 -> 3
  Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3],
  [1,3,4]

Constraints:
- 1 <= nums.length <= 2 * 10**4
- 1 <= nums[i], k <= nums.length
"""


class Solution:
    def subarraysWithKDistinct(self, nums: list[int], k: int) -> int:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    assert solution.subarraysWithKDistinct([1, 2, 1, 2, 3], 2) == 7
    assert solution.subarraysWithKDistinct([1, 2, 1, 3, 4], 3) == 3

    assert solution.subarraysWithKDistinct([1], 1) == 1
    assert solution.subarraysWithKDistinct([1, 1, 1, 1], 1) == 10
    assert solution.subarraysWithKDistinct([1, 1, 1, 1], 2) == 0
    assert solution.subarraysWithKDistinct([1, 2, 3], 3) == 1
    assert solution.subarraysWithKDistinct([1, 2, 3, 4], 4) == 1
    assert solution.subarraysWithKDistinct([1, 2, 3, 4], 1) == 4

    assert solution.subarraysWithKDistinct([1, 2, 1, 2, 1], 2) == 10
    assert solution.subarraysWithKDistinct([2, 2, 1, 1, 3, 3, 2], 3) == 8
    assert solution.subarraysWithKDistinct([3, 1, 3, 1, 2, 2, 4, 1], 3) == 10
    assert solution.subarraysWithKDistinct([2, 1, 1, 1, 2, 3, 3, 1], 2) == 11

    n = 20_000
    assert solution.subarraysWithKDistinct([1] * n, 1) == 200_010_000
    assert solution.subarraysWithKDistinct(list(range(1, n + 1)), 1) == n
    assert solution.subarraysWithKDistinct(list(range(1, n + 1)), n) == 1
    assert solution.subarraysWithKDistinct([1, 2] * (n // 2), 1) == n
    assert solution.subarraysWithKDistinct([1, 2] * (n // 2), 2) == 199_990_000


if __name__ == "__main__":
    main()
