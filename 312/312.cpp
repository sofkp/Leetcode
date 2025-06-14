class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int len = 2; len < n; len++) { //tam del intervalo
            for (int l = 0; l < n-len; l++) { //left
                int r = l+len; //right
                for (int i = l+1; i < r; i++) {
                    dp[l][r] = max(dp[l][r], dp[l][i] + dp[i][r] + nums[l]*nums[i]*nums[r]);
                }
            }
        }

        return dp[0][n-1];
    }
};
