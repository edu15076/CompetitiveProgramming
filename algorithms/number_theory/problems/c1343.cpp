#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

int main() { _
    int t; cin >> t;

    while (t--) {
        int n; cin >> n;
        for (int i = 2; i < 32; ++i)
            if (int sumPow2 {(1 << i) - 1}; not (n % sumPow2)) {
                cout << n / sumPow2 << endl;
                break;
            }
    }
    
    return 0;
}
