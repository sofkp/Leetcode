class Solution {
public:
    vector<vector<int>> dp; // dp[node][color]
    vector<vector<int>> graph; // adjacency list
    vector<int> visited; // 0 = unvisited, 1 = visited
    bool hasCycle = false;

    vector<int> dfs(int node, unordered_set<int>& curr_path, string& colors){
        vector<int> col_c(26, 0);
        if (curr_path.count(node)) {// cycle
            hasCycle = true;
            return col_c;
        }
        if (visited[node]) return dp[node];   // already processed

        curr_path.insert(node);

        for (int v : graph[node]) {
            vector<int> child = dfs(v, curr_path, colors);
            if (hasCycle) return col_c; // stop recursion if cycle
            for (int c = 0; c < 26; c++) {
                col_c[c] = max(col_c[c], child[c]);
            }
        }
        

        // update colors count
        col_c[colors[node] - 'a']++;
        dp[node] = col_c;
        visited[node] = 1;

        curr_path.erase(node); // end of process for node, erase to continue dfs
        return dp[node];
    }

    int largestPathValue(string colors, vector<vector<int>>& edges) {
         int n = colors.size();
        graph.assign(n, {});

        for (auto& e : edges) {
            graph[e[0]].push_back(e[1]);
        }

        dp.assign(n, vector<int>(26, 0));
        visited.assign(n, 0);
        hasCycle = false;

        int res = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                unordered_set<int> curr_path;
                vector<int> val = dfs(i, curr_path, colors);
                if (hasCycle) return -1;
                for (int c = 0; c < 26; c++) {
                    res = max(res, val[c]);
                }
            }
        }

        if (hasCycle) return -1;
        return res;
    }
};