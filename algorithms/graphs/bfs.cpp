#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

vector<uint> bfs(uint v, const vector<vector<uint>> &g) {
    queue<uint> q;
    q.push(v);

    vector<uint> dist(g.size(), UINT32_MAX);
    dist[v] = 0;

    while (not q.empty()) {
        v = q.front(); q.pop();

        for (auto u : g[v])
            if (uint w = dist[v] + 1; dist[u] > w) {
                dist[u] = w;
                q.push(u);
            }
    }

    return dist;
}

bool position_is_valid(pair<int, int> pos, const vector<vector<uint>> &matrix) {
    return pos.first >= 0 and pos.second >= 0 and pos.first < matrix.size() and pos.second < matrix[0].size();
}

vector<vector<uint>> bfs_matrix(pair<int, int> v, const vector<vector<uint>> &matrix, const vector<pair<int, int>> &moves) {
    queue<pair<int, int>> q;
    q.push(v);

    vector<vector<uint>> dist(matrix.size(), vector<uint>(matrix[0].size(), UINT32_MAX));
    dist[v.first][v.second] = 0;

    while (not q.empty()) {
        v = q.front(); q.pop();

        for (auto move : moves) {
            pair<int, int> u {move.first + v.first, move.second + v.second};
            uint w = dist[v.first][v.second] + 1;
            if (position_is_valid(u, matrix) and dist[u.first][u.second] > w) {
                dist[u.first][u.second] = w;
                q.push(u);
            }
        }
    }

    return dist;
}
