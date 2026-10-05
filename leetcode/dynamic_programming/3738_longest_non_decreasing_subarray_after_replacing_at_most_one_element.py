"""3738. Longest Non-Decreasing Subarray After Replacing at Most One Element.

Difficulty: Medium
https://leetcode.com/problems/longest-non-decreasing-subarray-after-replacing-at-most-one-element/

Reported in a Google L4 interview dated August 2026, not an intern interview.
The candidate report was published September 6, 2026; this is not an
independently verified or official Google question list.
https://prachub.com/interview-experiences/google-software-engineer-interview-experience-an-l4-loop-downleveled-to-l3

You are given an integer array nums. You may replace at most one element
with any other integer value of your choice.

Return the length of the longest non-decreasing subarray obtainable after
at most one replacement. A subarray is a contiguous, nonempty portion of
an array. Non-decreasing means each element is greater than or equal to
the previous element, if one exists.

Example 1:
Input: nums = [1, 2, 3, 1, 2]
Output: 4
Explanation: Replace nums[3] with 3 to obtain [1, 2, 3, 3, 2].
The longest non-decreasing subarray is [1, 2, 3, 3], of length 4.

Example 2:
Input: nums = [2, 2, 2, 2, 2]
Output: 5
Explanation: The entire array is already non-decreasing.

Constraints:
- 1 <= len(nums) <= 100000
- -1000000000 <= nums[i] <= 1000000000
"""


class Solution:
    def longestSubarray(self, nums: list[int]) -> int:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    assert solution.longestSubarray([7]) == 1
    assert solution.longestSubarray([9, 1]) == 2
    assert solution.longestSubarray([5, 4, 3, 2, 1]) == 2
    assert solution.longestSubarray([-5, -3, -3, 0, 8]) == 5

    assert solution.longestSubarray([100, 1, 2, 3]) == 4
    assert solution.longestSubarray([1, 2, 3, -100]) == 4
    assert solution.longestSubarray([1, 2, 99, 3, 4]) == 5
    assert solution.longestSubarray([1, 2, 9, 0, 3, 4]) == 4
    assert solution.longestSubarray([1, 4, 2, 3, 5, 0, 6]) == 5

    assert solution.longestSubarray(
        [-1000000000, 1000000000, -1000000000, 1000000000]
    ) == 4
    assert solution.longestSubarray([7] * 100000) == 100000


if __name__ == "__main__":
    main()
