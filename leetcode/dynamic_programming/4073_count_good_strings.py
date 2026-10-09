"""4073. Count Good Strings (Hard).

https://leetcode.com/problems/count-good-strings/

You are given an integer n. A string is good if it uses only 'a' and 'b'
and satisfies either of these rules:
- It contains exactly one distinct character and has odd length.
- It can be split into two non-empty good strings whose touching characters
  are different: the last character of the first part differs from the first
  character of the second part.

Return the number of good strings of length n, modulo 10**9 + 7.

Examples:
- n = 4 -> 6
- n = 3 -> 4
- n = 2 -> 2

Constraints:
- 1 <= n <= 10**15
"""


class Solution:
    def countGoodStrings(self, n: int) -> int:
        raise NotImplementedError


def main() -> None:
    solution = Solution()

    assert solution.countGoodStrings(1) == 2
    assert solution.countGoodStrings(2) == 2
    assert solution.countGoodStrings(3) == 4
    assert solution.countGoodStrings(4) == 6
    assert solution.countGoodStrings(5) == 10
    assert solution.countGoodStrings(6) == 16

    assert solution.countGoodStrings(10) == 110
    assert solution.countGoodStrings(15) == 1220
    assert solution.countGoodStrings(10**15) == 296650267


if __name__ == "__main__":
    main()
