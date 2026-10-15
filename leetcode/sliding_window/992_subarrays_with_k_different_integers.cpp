/*
 * 992. Subarrays with K Different Integers (Hard)
 *
 * https://leetcode.com/problems/subarrays-with-k-different-integers/
 *
 * Given an integer array nums and an integer k, return the number of good
 * subarrays of nums.
 *
 * A good array is an array where the number of different integers in that
 * array is exactly k.
 * - For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
 *
 * A subarray is a contiguous part of an array.
 *
 * Examples:
 * - nums = [1,2,1,2,3], k = 2 -> 7
 *   Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2],
 *   [2,3], [1,2,1], [2,1,2], [1,2,1,2]
 * - nums = [1,2,1,3,4], k = 3 -> 3
 *   Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3],
 *   [1,3,4]
 *
 * Constraints:
 * - 1 <= nums.length <= 2 * 10^4
 * - 1 <= nums[i], k <= nums.length
 */

#include <cassert>
#include <numeric>
#include <vector>
#include <unordered_map> 

using namespace std;

class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        auto get_windows = [&nums](int k) {
            unordered_map<int, int> window;         
            int ans = 0, l = 0; 
            
            for(int r = 0; r < nums.size(); r++) {
                window[nums[r]]++; 
                
                while (window.size() > k) {
                    int val = nums[l];
                    window[val] -= 1; 

                    if (window[val] == 0) window.erase(val);
                    l++; 
                }
                ans += r - l + 1; // all windows with at most k elements (could have less)
            }
            
            return ans; 
        };

        return get_windows(k) - get_windows(k-1); 
    }
};

int main() {
    Solution solution;

    {
        vector<int> nums = {1, 2, 1, 2, 3};
        assert(solution.subarraysWithKDistinct(nums, 2) == 7);
    }

    {
        vector<int> nums = {1, 2, 1, 3, 4};
        assert(solution.subarraysWithKDistinct(nums, 3) == 3);
    }

    {
        vector<int> nums = {1};
        assert(solution.subarraysWithKDistinct(nums, 1) == 1);
    }

    {
        vector<int> nums = {1, 1, 1, 1};
        assert(solution.subarraysWithKDistinct(nums, 1) == 10);
        assert(solution.subarraysWithKDistinct(nums, 2) == 0);
    }

    {
        vector<int> nums = {1, 2, 3};
        assert(solution.subarraysWithKDistinct(nums, 3) == 1);
    }

    {
        vector<int> nums = {1, 2, 3, 4};
        assert(solution.subarraysWithKDistinct(nums, 4) == 1);
        assert(solution.subarraysWithKDistinct(nums, 1) == 4);
    }

    {
        vector<int> nums = {1, 2, 1, 2, 1};
        assert(solution.subarraysWithKDistinct(nums, 2) == 10);
    }

    {
        vector<int> nums = {2, 2, 1, 1, 3, 3, 2};
        assert(solution.subarraysWithKDistinct(nums, 3) == 8);
    }

    {
        vector<int> nums = {3, 1, 3, 1, 2, 2, 4, 1};
        assert(solution.subarraysWithKDistinct(nums, 3) == 10);
    }

    {
        vector<int> nums = {2, 1, 1, 1, 2, 3, 3, 1};
        assert(solution.subarraysWithKDistinct(nums, 2) == 11);
    }

    const int n = 20000;

    {
        vector<int> nums(n, 1);
        assert(solution.subarraysWithKDistinct(nums, 1) == 200010000);
    }

    {
        vector<int> nums(n);
        iota(nums.begin(), nums.end(), 1);
        assert(solution.subarraysWithKDistinct(nums, 1) == n);
        assert(solution.subarraysWithKDistinct(nums, n) == 1);
    }

    {
        vector<int> nums(n);
        for (int i = 0; i < n; i++) nums[i] = i % 2 + 1;
        assert(solution.subarraysWithKDistinct(nums, 1) == n);
        assert(solution.subarraysWithKDistinct(nums, 2) == 199990000);
    }

    return 0;
}
