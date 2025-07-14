// https://leetcode.com/problems/majority-element
// 2025-07-14

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ans = 0;
        unordered_map<int, int> numMap;
        int n = nums.size();

        // 각 숫자 몇 개 있는지 count
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            numMap[num]++;
        }

        // 절반 이상 있다면 그 숫자 출력
        for (auto k : numMap) {
            if (k.second > n/2) {
                ans = k.first;
                break;
            }
        }

        return ans;
    }
};