/*
 * 30. Substring with Concatenation of All Words (Hard)
 *
 * https://leetcode.com/problems/substring-with-concatenation-of-all-words/
 *
 * You are given a string s and an array of strings words. All the strings of
 * words are of the same length.
 *
 * A concatenated string is a string that exactly contains all the strings of
 * any permutation of words concatenated.
 * - For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd",
 *   "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings.
 *   "acdbef" is not a concatenated string because it is not the concatenation
 *   of any permutation of words.
 *
 * Return an array of the starting indices of all the concatenated substrings
 * in s. You can return the answer in any order.
 *
 * Examples:
 * - s = "barfoothefoobarman", words = ["foo","bar"] -> [0,9]
 *   The substring starting at 0 is "barfoo". It is the concatenation of
 *   ["bar","foo"] which is a permutation of words.
 *   The substring starting at 9 is "foobar". It is the concatenation of
 *   ["foo","bar"] which is a permutation of words.
 * - s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"] -> []
 *   There is no concatenated substring.
 * - s = "barfoofoobarthefoobarman", words = ["bar","foo","the"] -> [6,9,12]
 *   The substring starting at 6 is "foobarthe". It is the concatenation of
 *   ["foo","bar","the"].
 *   The substring starting at 9 is "barthefoo". It is the concatenation of
 *   ["bar","the","foo"].
 *   The substring starting at 12 is "thefoobar". It is the concatenation of
 *   ["the","foo","bar"].
 *
 * Constraints:
 * - 1 <= s.length <= 10^4
 * - 1 <= words.length <= 5000
 * - 1 <= words[i].length <= 30
 * - s and words[i] consist of lowercase English letters.
 *
 * 1. convert words into a set  
 * 2. if the window is in that set, it's a valid start. keep track of all starts
 * let's use a hashmap to keep track of words found / window. if len(window) is len(words) then we found
 * a match. increment l until we're at the next word start.
 *
 *
 * s = "foohellobarfoo", ["bar", "foo"]
 * bank = {bar, foo} 
 * wind = {foo: 0} word, idx found
 * then we find h, making  
 *
 *
 *
 * this is the major hurdle: skipping invalid starts
 */

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <unordered_set> 
#include <unordered_map>
#include <iostream> 

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;
        
        int total = words.size(); 
        unordered_map<string, int> bank; 
        unordered_map<string, int> window; 
        
        for(int i = 0; i < total; i++) {
            bank[words[i]]++; 
        }
        
        int k = words[0].size();
        for(int i = 0; i < k; i++) {
            int l = i, r = i; 
            int matches = 0; 
            window = bank; 
            while(r + k <= s.size()) {
                string curr = s.substr(r, k); // k chars, starting from r
                
                if(!window.contains(curr)) { 
                    l = r+k;
                    window = bank; 
                    matches = 0; 
                } else {
                    while(window[curr] == 0) {
                        window[s.substr(l, k)]++; 
                        l += k;
                        matches--; 
                    }
                    matches++;
                    window[curr]--; 
                }
                
                if(matches == total) ans.push_back(l); 
                r += k;  
            }     
        } 
        return ans;
    }
};

// The answer may be returned in any order, so tests compare sorted results.
vector<int> sorted(vector<int> values) {
    sort(values.begin(), values.end());
    return values;
}

int main() {
    Solution solution;

    {
        vector<string> words = {"foo", "bar"};
        assert(sorted(solution.findSubstring("barfoothefoobarman", words)) == vector<int>({0, 9}));
    }

    {
        vector<string> words = {"word", "good", "best", "word"};
        assert(solution.findSubstring("wordgoodgoodgoodbestword", words).empty());
    }

    {
        vector<string> words = {"bar", "foo", "the"};
        assert(sorted(solution.findSubstring("barfoofoobarthefoobarman", words)) == vector<int>({6, 9, 12}));
    }

    {
        vector<string> words = {"a"};
        assert(solution.findSubstring("a", words) == vector<int>({0}));
    }

    {
        vector<string> words = {"b"};
        assert(solution.findSubstring("a", words).empty());
    }

    {
        vector<string> words = {"abc"};
        assert(solution.findSubstring("ab", words).empty());
    }

    {
        vector<string> words = {"a", "b", "a"};
        assert(solution.findSubstring("ab", words).empty());
    }

    {
        vector<string> words = {"bar", "foo"};
        assert(solution.findSubstring("xbarfoo", words) == vector<int>({1}));
    }

    {
        vector<string> words = {"aa", "aa"};
        assert(sorted(solution.findSubstring("aaaaaa", words)) == vector<int>({0, 1, 2}));
    }

    {
        vector<string> words = {"word", "good", "best", "good"};
        assert(solution.findSubstring("wordgoodgoodgoodbestword", words) == vector<int>({8}));
    }

    {
        vector<string> words = {"fooo", "barr", "wing", "ding", "wing"};
        string s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
        assert(solution.findSubstring(s, words) == vector<int>({13}));
    }

    {
        vector<string> words = {"foo", "bar", "foo"};
        assert(sorted(solution.findSubstring("foobarfoobarfoo", words)) == vector<int>({0, 6}));
    }

    {
        vector<string> words = {"ab", "ba"};
        assert(solution.findSubstring("abababab", words).empty());
    }

    {
        vector<string> words = {"ab", "ab"};
        assert(sorted(solution.findSubstring("abababab", words)) == vector<int>({0, 2, 4}));
    }

    {
        vector<string> words = {"cat", "dog"};
        assert(sorted(solution.findSubstring("catdogcatdogcat", words)) == vector<int>({0, 3, 6, 9}));
    }

    {
        vector<string> words(5000, "a");
        vector<int> result = sorted(solution.findSubstring(string(10000, 'a'), words));
        assert(result.size() == 5001);
        assert(result.front() == 0 && result.back() == 5000);
    }

    {
        vector<string> words(300, string(30, 'a'));
        vector<int> result = sorted(solution.findSubstring(string(10000, 'a'), words));
        assert(result.size() == 1001);
        assert(result.front() == 0 && result.back() == 1000);
    }

    {
        string s;
        for (int i = 0; i < 2500; i++) s += "abcd";

        vector<string> words;
        for (int i = 0; i < 50; i++) {
            words.push_back("bc");
            words.push_back("da");
        }

        vector<int> result = sorted(solution.findSubstring(s, words));
        assert(result.size() == 4900);
        assert(result.front() == 1 && result.back() == 9799);
        assert(all_of(result.begin(), result.end(), [](int start) { return start % 2 == 1; }));
    }

    {
        vector<string> words(5000, "b");
        assert(solution.findSubstring(string(10000, 'a'), words).empty());
    }

    return 0;
}
