class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto& f : flights) { //lista de adjacencia (grafo)
            graph[f[0]].emplace_back(f[1], f[2]);
        }

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.emplace(0, src, 0); //primer nodo, del source al source

        vector<int> minStops(n, INT_MAX); 
        //vector que guarda la cantidad de stops utilizados

        while (!pq.empty()) {
            auto [cost, a, stops] = pq.top(); 
            pq.pop();

            if (a == dst) return cost;

            if (stops > k || stops > minStops[a]) continue;
            minStops[a] = stops;

            for (auto& [b, w] : graph[a]) {
                pq.emplace(cost + w, b, stops + 1);
            }
        }

        return -1;
    }
};
