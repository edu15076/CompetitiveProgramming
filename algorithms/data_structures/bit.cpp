#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;
typedef unsigned long long ull;
typedef long long ll;

class BIT {
public:
    BIT(const size_t n) {
        m_bin = vector<ll>(n + 1, 0);
    }

    void add(size_t pos, ll value) {
        for ( ; pos < m_bin.size(); pos += pos & -pos)
            m_bin[pos] += value;
    }

    ll query(size_t pos) {
        ull sum {0};
        for ( ; pos > 0; pos -= pos & -pos)
            sum += m_bin[pos];
        return sum;
    }
private:
    vector<ll> m_bin;
};

vector<uint> lower_right(const vector<uint> &v, const uint max_item) {
    const int n = v.size();
    BIT bit(max_item);
    vector<uint> lower(n);

    for (int i {n - 1}; i >= 0; i--) {
        lower[i] = bit.query(v[i] - 1);
        bit.add(v[i], 1);
    }
    return lower;
}
