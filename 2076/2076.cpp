class DSU {
    vector<int> rank, parent;

public:
    DSU(int n) {
        rank.resize(n, 0);
        parent.resize(n);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]); 
        }
        return parent[i];
    }

    void unionSet(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot == yRoot) return; 

        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else if (rank[yRoot] < rank[xRoot]) {
            parent[yRoot] = xRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }
    bool sameSet(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        DSU dsu(n); // successful connections
        vector<unordered_set<int>> restrictionList(n); //list of restrictions of each user
        vector<bool> res;

        // restricciones iniciales
        for (auto r : restrictions) {
            restrictionList[r[0]].insert(r[1]);
            restrictionList[r[1]].insert(r[0]);
        }

        for (auto r : requests) {
            int u = r[0];
            int v = r[1];

            int pu = dsu.find(u);
            int pv = dsu.find(v);

            // check if restriction between pu and pv (directly/indirectly restricted)
            bool canJoin = true;

            for (int x : restrictionList[pu]) { // restrictions of pu in pv's friends
                if (dsu.sameSet(x, pv)) {
                    canJoin = false;
                    break;
                }
            }
            if (canJoin) {
                for (int y : restrictionList[pv]) { // restrictions of pv in pu's friends
                    if (dsu.sameSet(y, pu)) {
                        canJoin = false;
                        break;
                    }
                }
            }

            if (canJoin) {// merge friends
                dsu.unionSet(u, v);

                // merge restriction lists
                int newParent = dsu.find(u);

                int old_pu = pu, old_pv = pv;
                if (old_pu != old_pv) {
                    for (int x : restrictionList[old_pv]) { //merge pv's restriction to pu
                        restrictionList[old_pu].insert(x);
                    }
                    for (int x : restrictionList[old_pu]) { //merge pu's restriction to pu
                        restrictionList[old_pv].insert(x);
                    }
                    // merge pu and pv's restriction and add to the new parent 
                    restrictionList[newParent] = restrictionList[old_pu];
                    for (int x : restrictionList[old_pv])
                        restrictionList[newParent].insert(x);
                }
                res.push_back(true);
            } else {
                res.push_back(false);
            }
        }

        return res;
    }
};