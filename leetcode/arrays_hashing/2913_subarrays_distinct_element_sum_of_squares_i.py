"""2913. Subarrays Distinct Element Sum of Squares I (Easy).

https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/

You are given a 0-indexed integer array nums.

The distinct count of a subarray of nums is defined as:
- Let nums[i..j] be a subarray of nums consisting of all the indices from i
  to j such that 0 <= i <= j < nums.length. Then the number of distinct values
  in nums[i..j] is called the distinct count of nums[i..j].

Return the sum of the squares of distinct counts of all subarrays of nums.

A subarray is a contiguous non-empty sequence of elements within an array.

Examples:
- nums = [1,2,1] -> 15
  Six possible subarrays are:
  [1]: 1 distinct value
  [2]: 1 distinct value
  [1]: 1 distinct value
  [1,2]: 2 distinct values
  [2,1]: 2 distinct values
  [1,2,1]: 2 distinct values
  The sum of the squares of the distinct counts in all subarrays is equal to
  1^2 + 1^2 + 1^2 + 2^2 + 2^2 + 2^2 = 15.
- nums = [1,1] -> 3
  Three possible subarrays are:
  [1]: 1 distinct value
  [1]: 1 distinct value
  [1,1]: 1 distinct value
  The sum of the squares of the distinct counts in all subarrays is equal to
  1^2 + 1^2 + 1^2 = 3.

Constraints:
- 1 <= nums.length <= 100
- 1 <= nums[i] <= 100

# of distinct values from i to j is distinct count of nusm[i to j]
#
[1, 2, 3] -> distinct count = 3 

problem asks to find all subarrays, then find the sum of squares of them
"""


class Solution:
    def sumCounts(self, nums: list[int]) -> int:
        n = len(nums) 
        ans = 0 
        
        for i in range(n): 
            seen = set()
            for j in range(i, n):
                seen.add(nums[j])
                ans += len(seen)**2

        return ans
                
                    


    

def main() -> None:
    solution = Solution()

    assert solution.sumCounts([1, 2, 1]) == 15
    assert solution.sumCounts([1, 1]) == 3

    assert solution.sumCounts([7]) == 1
    assert solution.sumCounts([1, 2]) == 6
    assert solution.sumCounts([1, 2, 3]) == 20
    assert solution.sumCounts([1, 2, 3, 4]) == 50
    assert solution.sumCounts([5, 5, 5, 5]) == 10

    assert solution.sumCounts([1, 2, 1, 2]) == 28
    assert solution.sumCounts([3, 1, 3, 2, 1]) == 70
    assert solution.sumCounts([4, 4, 2, 2, 4]) == 39
    assert solution.sumCounts([1, 2, 3, 2, 1]) == 70

    assert solution.sumCounts(list(range(1, 101))) == 8_670_850
    assert solution.sumCounts([100] * 100) == 5_050
    assert solution.sumCounts([1, 2] * 50) == 19_900
    assert solution.sumCounts([i % 10 + 1 for i in range(100)]) == 445_360


if __name__ == "__main__":
    main()
