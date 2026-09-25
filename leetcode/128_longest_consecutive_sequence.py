"""128. Longest Consecutive Sequence (Medium).

https://leetcode.com/problems/longest-consecutive-sequence/

An unsorted list of integers is given. Return the length of its longest
sequence of consecutive integer values. The values do not need to appear
next to each other in the input. The required running time is O(n).

Example 1:
Input: nums = [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The values 1, 2, 3, and 4 form a consecutive sequence.

Example 2:
Input: nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
Output: 9

Example 3:
Input: nums = [1, 0, 1, 2]
Output: 3

Constraints:
- 0 <= len(nums) <= 100000
- -1000000000 <= nums[i] <= 1000000000

Reported in a Google L4 application engineering interview:
https://leetcode.com/discuss/post/5147609/Google-L4-or-Application-Engineer-/

set = {1, 2, 3, 4, 100, 200}

"is the value above / below me in the set?" 

"4" -> not the start of the sequence (because there's a value beneath it, 3)

only start counting from sequence starts

1. convert input to set

for all values in input 
if val-1 is in the set, skip 
o.w. this is the start of the sequence
ask "while val+1 is in the set" start tracking length 
curr += 1 
ans 

{1, 2, 3, 4, 5, 6}

for every value in input 
O(N) + O(N) = O(N)

[1, 2, 3, 4, 1, 2, 3]
"""



class Solution:
    def longestConsecutive(self, nums: list[int]) -> int:
        if nums == []: return 0 

        chain = set(nums) # {100, 200, 4, 3, 2, 1}
        ans = 1 
        
        for num in nums: 
            if num-1 in chain: 
                continue
            
            # now we're at the start of the sequence
            curr = 0 
            while num in chain:  
                chain.remove(num)
                
                curr += 1
                num += 1 
                
            
            ans = max(ans, curr)
        
        return ans 

def main() -> None:
    solution = Solution()

    assert solution.longestConsecutive([]) == 0
    assert solution.longestConsecutive([42]) == 1
    assert solution.longestConsecutive([5, 5, 5]) == 1
    assert solution.longestConsecutive([100, 4, 200, 1, 3, 2]) == 4
    assert solution.longestConsecutive([1, 0, 1, 2]) == 3
    assert solution.longestConsecutive([10, 2, 1, 3, -2, -1, 0]) == 6
    assert solution.longestConsecutive([5, 2, 99, 3, 4]) == 4
    assert solution.longestConsecutive([-1000000000, 1000000000]) == 1


if __name__ == "__main__":
    main()
