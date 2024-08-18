#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

class PrefixSum {
public:
    vector<uint> s;

    explicit PrefixSum(const vector<uint>& base) {
        s = vector<uint>(base.size());
        s[0] = base[0];

        for (uint i {1}; i < s.size(); i++)
            s[i] = s[i - 1] + base[i];
    }

    uint get(uint start, uint end) {
        return start ? s[end] - s[start - 1] : s[end];
    }

    uint get(uint pos) {
        return get(0, pos);
    }

    uint size() {
        return s.size();
    }
};
