#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"
#define NOT_VISITED 0

typedef unsigned uint;

void dfs(uint v, vector<bool> &visited, const vector<vector<uint>> &g) {
    visited[v] = true;

    for (auto u : g[v])
        if (not visited[u])
            dfs(u, visited, g);
}

void iterative_dfs(uint v, vector<bool> &visited, const vector<vector<uint>> &g) {
    stack<uint> stk;
    stk.push(v);

    while (not stk.empty()) {
        v = stk.top(); stk.pop();
        visited[v] = true;

        for (auto u : g[v])
            if (not visited[u])
                stk.push(u);
    }
}

uint color_graph(uint v, uint color, vector<uint> &colors, const vector<vector<uint>> &g) {
    colors[v] = color;

    for (auto u : g[v])
        if (colors[u] != NOT_VISITED)
            color = color_graph(u, color + 1, colors, g);
    return color;
}
