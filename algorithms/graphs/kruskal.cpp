#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

class DisjointSet {
    vector<uint> parent;

public:
    DisjointSet(uint n) : parent(n) {
        for (uint i {0}; i < n; i++)
            parent[i] = i;
    }

    uint find(uint v) {
        if (parent[v] != v)
            parent[v] = find(parent[v]);
        return parent[v];
    }

    void join(uint v, uint u) {
        parent[find(u)] = find(v);
    }

    bool are_in_same_set(uint v, uint u) {
        return find(v) == find(u);
    }
};

vector<tuple<uint, uint, uint>> agm(const uint n, const vector<tuple<uint, uint, uint>> &edges) {
    DisjointSet forest(n);
    vector<tuple<uint, uint, uint>> taken_edges;

    for (auto &[w, v, u] : edges)
        if (not forest.are_in_same_set(v, u)) {
            forest.join(v, u);
            taken_edges.emplace_back(w, v, u);
        }

    return taken_edges;
}
