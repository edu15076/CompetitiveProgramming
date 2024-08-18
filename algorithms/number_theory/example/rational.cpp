#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef long long ll;

pair<ll, ll> toFraction(double n, unsigned p) {
    const ll tenP = (ll) pow(10, p);
    const ll t = (ll) (n * tenP);
    const ll rMdc = gcd(t, tenP);
    return {t / rMdc, tenP / rMdc};
}

int main() { _
    double n; cin >> n;
    auto nFrac = toFraction(n, 3);

    cout << fixed << setprecision(3);
    cout << n << " = " << nFrac.first << " / " << nFrac.second << endl;

    cout << fixed << setprecision(18) << (long double) n + 0.000000000000000001 << " " << n + 0.000000000000000001 << endl;
    
    return 0;
}
