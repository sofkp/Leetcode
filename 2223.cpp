//2223. Sum of Scores of built strings
class Solution {
public:
    long long sumScores(string s) {
        int n = s.size();
        if (n == 0) return 0;
        
        vector<int> Z(n, 0);
        Z[0] = n; 
        int izq = 0, der = 0;
        
        for (int i = 1; i < n; ++i) {
            if (i > der) {
                // Case 1: i is outside current Z-box
                izq = der = i;
                while (der < n && s[der - izq] == s[der]) {
                    der++;
                }
                Z[i] = der - izq;
                der--;
            } else {
                // Case 2: i is inside current Z-box
                int k = i - izq;
                if (Z[k] < der - i + 1) {
                    Z[i] = Z[k];
                } else {
                    izq = i;
                    while (der < n && s[der - izq] == s[der]) {
                        der++;
                    }
                    Z[i] = der - izq;
                    der--;
                }
            }
        }
        long long total = 0;
        for (int num : Z) {
            total += num;
        }
        return total;
    }
};
