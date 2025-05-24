class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;  // baso case
        
        for (int i = 1; i <= n; ++i) {
            int tt_a = 0;
            int maxi_h = 0;
            for (int j = i; j > 0; --j) {
                tt_a += books[j-1][0];
                if (tt_a > shelfWidth) {
                    break;
                }
                maxi_h = max(maxi_h, books[j-1][1]);
                dp[i] = min(dp[i], dp[j-1] + maxi_h);
            }
        }
        
        return dp[n];
    }
};