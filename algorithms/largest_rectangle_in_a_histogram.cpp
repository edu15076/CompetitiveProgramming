#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;
typedef unsigned long long ull;

ull find_greatest_rectangle(const vector<uint>& v) {
    const uint n = v.size();
    vector<uint> leftSmall(n, -1), rightSmall(n, n);
    stack<uint> s;
    s.push(-1);
    s.push(0);

    for (int i {1}; i < n; s.push(i++)) {
        while (s.top() != -1 and v[s.top()] > v[i]) {
            rightSmall[s.top()] = i;
            s.pop();
        }

        if (v[i] != v[i - 1])
            leftSmall[i] = s.top();
        else
            leftSmall[i] = leftSmall[i - 1];
    }

    ull maxRect {0};
    for (uint i {0}; i < n; ++ i)
        if (const ull base = rightSmall[i] - leftSmall[i] - 1; base and v[i])
            maxRect = max(maxRect, v[i] * base);

    return maxRect;
}
