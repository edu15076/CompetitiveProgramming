#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

void ssdc(vector<int> &c, vector<int> &a, int m) {
    uint j = upper_bound(c.begin(), c.end(), a[m]) - c.begin();
    if (c[j - 1] < a[m] and a[m] < c[j])
        c[j] = a[m];
}

uint ssc(vector<int> &a) {
    uint n = a.size();
    vector<int> c(n + 1, INT32_MAX);
    c[0] = -INT32_MAX;

    for (int i {0}; i < n; i++)
        ssdc(c, a, i);

    uint max_ssc {0};
    for (uint i {0}; i <= n; i++)
        if (c[i] < INT32_MAX)
            max_ssc = i;

    return max_ssc;
}
