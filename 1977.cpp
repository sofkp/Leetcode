//1977. Number of ways to separate numbers
class Solution {
    long mod = 1e9+7;
    long LCP(vector<vector<long>> &dp, vector<vector<int>> &lcp, string &s, int n, int i, int j) {
        if ((i + j) == n) {
            return 1;
        }
        if (i + j > n) {
            return 0;
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        long ans = 0;
        if (s[i] == '0') return 0;
        ans =  LCP(dp, lcp,s, n, i, j + 1) % mod;
        if ((i + j) != 0 && s[i+j] != '0') {
            int common_len = lcp[i][i+j];
            if (common_len >= j || ((i + j + common_len) < n && s[i + common_len] <= s[i + j + common_len])) {
                ans = (ans + LCP(dp, lcp, s, n, i + j, j)) % mod;
            } else {
                ans = (ans +  LCP(dp, lcp, s, n, i + j, j + 1) % mod) % mod;
            }
        }
        dp[i][j] = ans % mod;
        return ans;
    }
public:
    int numberOfCombinations(string num) {
        int n = num.length();
        vector<vector<long>> dp(n + 1, vector<long> (n + 1, -1));
        vector<vector<int>> lcp(n+1, vector<int>(n+1, 0)); 
        for(int i=n-1; i>=0; --i){
            for(int j=n-1; j>=0; --j){
                if(num[i]==num[j]){
                    lcp[i][j] = lcp[i+1][j+1]+1;
                }
            }
        }
        return LCP(dp, lcp, num, n, 0, 0);
    }
};
