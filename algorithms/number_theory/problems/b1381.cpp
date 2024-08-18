// https://www.beecrowd.com.br/judge/pt/problems/view/1381

#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"
#define MOD 1300031

uint64_t f(uint64_t n, uint64_t c) {
    if (n == 1)
        return 1;
    uint64_t s {0};
    for (uint64_t i {0}; i <= c; ++i)
        s = (s + f(n - 1, i)) % MOD;
    return s;
}

int main() { _
    uint64_t t; cin >> t;

    while (t--) {
        uint64_t n, c; cin >> n >> c;
        cout << f(n, c) << endl;
    }
    
    return 0;
}
