// https://leetcode.com/problems/letter-combinations-of-a-phone-number
// 2025-07-15

class Solution {
public:
    vector<string> ans;
    unordered_map<char, string> digitsToLetters = {  // 숫자 - 문자
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
    };

    vector<string> letterCombinations(string digits) {
        // 빈 문자열 -> 바로 종료
        if (digits.empty()) {
            return ans;
        }

        string temp;
        bt(0, digits.size(), temp, digits);

        return ans;
    }

    void bt(int idx, int size, string& temp, const string& digits) {
        if (temp.size() == size) {
            ans.push_back({temp});
            return;
        }

        // map에서 string 가져오기
        string letters = digitsToLetters.at(digits[idx]);

        for (int i = 0; i < letters.size(); i++) {
            temp.push_back(letters[i]);
            bt(idx+1, size, temp, digits);
            temp.pop_back();
        }
    }
};