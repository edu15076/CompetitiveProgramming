#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

vector<uint> dijkstra(uint source, const vector<vector<pair<uint, uint>>> &g) {
    priority_queue<pair<uint, uint>, vector<pair<uint, uint>>, greater<>> pq;
    pq.emplace(0, source);

    vector<uint> dist(g.size(), UINT32_MAX);
    dist[source] = 0;

    while (not pq.empty()) {
        auto [v_weight, v] = pq.top(); pq.pop();

        if (v_weight > dist[v])
            continue;

        for (auto [u_weight, u] : g[v]) {
            uint w = v_weight + u_weight;
            if (w >= dist[u])
                continue;
            dist[u] = w;
            pq.emplace(w, u);
        }
    }

    return dist;
}
