#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"
#define VISITED (-1)

typedef unsigned uint;

// kahn
vector<uint> topological_sort(const vector<vector<uint>> &g, vector<uint> &degree) {
    const uint n = g.size();
    priority_queue<uint, vector<uint>, greater<>> pq;
    vector<uint> topological_order;

    for (uint i {0}; i < n; i++)
        if (not degree[i])
            pq.push(i);

    while (not pq.empty()) {
        uint v = pq.top(); pq.pop();

        degree[v] = VISITED;
        topological_order.push_back(v);

        for (auto u : g[v])
            if (degree[u] != VISITED) {
                degree[u]--;
                if (not degree[u]) pq.push(u);
            }
    }

    return topological_order;
}
