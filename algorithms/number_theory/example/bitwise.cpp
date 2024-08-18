#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

#define isOdd(n) (n & 1)
#define mult2ToTheN(m, n) (m << n)
#define div2ToTheN(m, n) (m >> n)
#define twoToTheN(n) (1 << n)
#define sig(n) ((n >> 31) | -(n >> 31))
#define greatest2powDivisorOf(n) (n & -n)

int main() { _
    int m, n; cin >> m >> n;

    dbg(isOdd(n));
    dbg(mult2ToTheN(m, n));
    dbg(div2ToTheN(m, n));
    dbg(twoToTheN(n));
    dbg(sig(n));
    dbg(greatest2powDivisorOf(n));

    return 0;
}
