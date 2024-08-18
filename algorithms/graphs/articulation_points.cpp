#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

uint _dfs_articulation_vertexes(const vector<vector<uint>>& adj, vector<bool>& visited, vector<uint>& depth,
                              vector<uint>& low, set<uint>& articulation_vertexes, uint v = 0, uint d = 0) {
    visited[v] = true;
    depth[v] = low[v] = d;

    uint children {0};

    for (auto u : adj[v]) {
        if (depth[u] == depth[v] - 1)
            continue;

        if (not visited[u]) {
            d = _dfs_articulation_vertexes(adj, visited, depth, low, articulation_vertexes, u, d + 1);
            ++children;
            low[v] = min(low[v], low[u]);
            if (low[u] >= depth[v] and (v or children > 1))
                articulation_vertexes.insert(v);
        } else
            // Quando chega em um que já foi visitado, então existe um caminho alternativo. Queremos o caminho alternativo
            // que volte o máximo possível
            low[v] = min(low[v], depth[u]);
    }

    return d;
}

set<uint> dfs_articulation_vertexes(const vector<vector<uint>> &g) {
    const uint n = g.size();
    vector<bool> visited(n, false);
    vector<uint> depth(n, UINT32_MAX), low(n, UINT32_MAX);
    set<uint> articulation_vertexes;
    _dfs_articulation_vertexes(g, visited, depth, low, articulation_vertexes);
    return articulation_vertexes;
}
