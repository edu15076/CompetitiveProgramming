#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

vector<uint> dijkstra(uint start, const vector<vector<pair<uint, uint>>> &g) {
    priority_queue<pair<uint, uint>, vector<pair<uint, uint>>, greater<>> pq;
    pq.emplace(0, start);

    vector<uint> dist(g.size(), UINT32_MAX);
    dist[start] = 0;

    while (not pq.empty()) {
        auto [vw, v] = pq.top(); pq.pop();

        for (auto [uw, u] : g[v])
            if (uint w = vw + uw; dist[u] > w) {
                dist[u] = w;
                pq.emplace(w, u);
            }
    }

    return dist;
}
