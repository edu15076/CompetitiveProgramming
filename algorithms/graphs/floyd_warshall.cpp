#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

void find_all_min_distances_passing_by_k(vector<vector<uint>>& distances, uint size, uint k) {
    for (uint i {0}; i < size; ++i)
        for (uint j {0}; j < size; ++j)
            distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
}

void floyd_warshall(vector<vector<uint>> &distances, uint size) {
    for (uint k {0}; k < size; ++k)
        find_all_min_distances_passing_by_k(distances, size, k);
}
