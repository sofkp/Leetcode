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
};

class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        DSU dsu(row*col + 2); // +2 para top y bottom
        vector<vector<int>> matrix(row+1, vector<int>(col+1, 0)); 

        int top = row * col;
        int bottom = row * col + 1;
        int direcs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 4 direcciones

        for (int dia = cells.size()-1; dia>=0; dia--) {
            int r = cells[dia][0];
            int c = cells[dia][1];
            matrix[r][c] = 1; 
            int pos = (r-1) * col + (c-1); // coordenada a pos en matrix

            // buscar y conectar con vecinos tierra
            for (auto& dir : direcs) {
                int r1 = r+dir[0];
                int c1 = c+dir[1];
                if (r1>=1 && r1<=row && c1>=1 && c1<=col && matrix[r1][c1]==1) {
                    int vecino = (r1-1) * col + (c1-1);
                    dsu.unionSet(pos, vecino);
                }
            }

            if (r == 1) {
                dsu.unionSet(pos, top);
            }
            if (r == row) {
                dsu.unionSet(pos, bottom);
            }
            // se encontró un camino
            if (dsu.find(top) == dsu.find(bottom)) {
                return dia;
            }
        }

        return 0; 
    }
};