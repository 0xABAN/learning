#include <cassert>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        // TODO: implement
        throw "not implemented";
    }
};

int main() {
    Solution solution;

    {
        vector<int> nums = {INT_MIN};
        assert(solution.findPeakElement(nums) == 0);
    }

    {
        vector<int> nums = {-4, 9};
        assert(solution.findPeakElement(nums) == 1);
    }

    {
        vector<int> nums = {9, -4};
        assert(solution.findPeakElement(nums) == 0);
    }

    {
        vector<int> nums = {-9, -3, 0, 2, 11};
        assert(solution.findPeakElement(nums) == 4);
    }

    {
        vector<int> nums = {11, 2, 0, -3, -9};
        assert(solution.findPeakElement(nums) == 0);
    }

    {
        vector<int> nums = {-8, -2, 6, 1, -7};
        assert(solution.findPeakElement(nums) == 2);
    }

    {
        vector<int> nums = {-5, 4, -1, 6, -2, 3, -8};
        int result = solution.findPeakElement(nums);
        assert(result == 1 || result == 3 || result == 5);
    }

    {
        vector<int> nums = {7, -3, 9};
        int result = solution.findPeakElement(nums);
        assert(result == 0 || result == 2);
    }

    {
        vector<int> nums = {INT_MIN, INT_MAX, INT_MIN};
        assert(solution.findPeakElement(nums) == 1);
    }

    return 0;
}
