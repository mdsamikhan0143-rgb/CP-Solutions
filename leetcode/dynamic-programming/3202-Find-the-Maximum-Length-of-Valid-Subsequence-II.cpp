
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        vector<vector<int>> dp(k, vector<int>(k, 0));
        int ans = 1;

        for (int num : nums) {
            int r = num % k;

            for (int j = 0; j < k; j++) {
                dp[j][r] = dp[r][j] + 1;
                ans = max(ans, dp[j][r]);
            }
        }

        return ans;
    }
};
