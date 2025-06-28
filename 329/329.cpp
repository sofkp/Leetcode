class Solution {
public:
    int dfs(int i, int j, int m, int n, const vector<vector<int>>& matrix, vector<vector<int>>& dp, const vector<pair<int, int>>& dirs) {
        
        if (dp[i][j] != 0) {
            return dp[i][j];
        }

        int longest = 1;

        for (const auto& dir : dirs) {
            int ii = i + dir.first;
            int jj = j + dir.second;

            if (ii>=0 && ii<m && jj>=0 && jj<n && matrix[ii][jj]>matrix[i][j]) {
                longest = max(longest, 1 + dfs(ii, jj, m, n, matrix, dp, dirs));
            }
        }

        dp[i][j] = longest;
        return longest;
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        int m = matrix.size();
        int n = matrix[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));
        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int maxi = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                maxi = max(maxi, dfs(i, j, m, n, matrix, dp, dirs));
            }
        }

        return maxi;
    }
};