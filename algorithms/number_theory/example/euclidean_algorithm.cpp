#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

unsigned mdc(unsigned a, unsigned b) {
    for (unsigned r {a % b}; r; a = b, b = r, r = a % b);
    return b;
}

unsigned mmc(unsigned a, unsigned b) {
    return a / mdc(a, b) * b;
}

tuple<unsigned, int, int> extendedEuclidian(unsigned a, unsigned b) {
    int x2 {1}, y2 {0}, x1 {0}, y1 {1};
    for (unsigned q {a / b}, r {a % b}; r; a = b, b = r, q = a / b, r = a % b) {
        const int x = x2 - x1 * q, y = y2 - y1 * q;
        x2 = x1; y2 = y1;
        x1 = x; y1 = y;
    }
    return {b, x1, y1};
}

unsigned int mod(int a, int n) {
    return (n + a % n) % n;
}

unsigned int inverse(int a, int n) {
    return mod(get<1>(extendedEuclidian(a, n)), n);
}

unsigned mod_pow(int base, unsigned exponent, int n) {
    if (not exponent)
        return 1;

    unsigned q {exponent >> 1}, r {exponent & 1};
    unsigned result = mod_pow(mod(base * base, n), q, n);

    return r ? mod(result * base, n) : result;
}

unsigned inverse_fermat(int a, int p) {
    return mod_pow(a, p - 2, p);
}

pair<int, int>* linearDiofantineEquation(unsigned a, unsigned b, unsigned c) {
    auto [mdcResult, alpha, beta] = extendedEuclidian(a, b);
    if (c % mdcResult)
        return nullptr;
    auto* solution = new pair<int, int>(alpha / mdcResult * c, beta / mdcResult * c);
    return solution;
}

int main() { _
    unsigned a, b; cin >> a >> b;
    auto dAlphaBeta = extendedEuclidian(a, b);

    cout << inverse_fermat(a, 7) << endl;

    cout << "mdc(a, b) = " << get<0>(dAlphaBeta) << ", alpha = " << get<1>(dAlphaBeta) << ", beta = " << get<2>(dAlphaBeta) << endl;
    dbg(lcm(a, b));

    dbg(gcd(a, b));
    dbg(lcm(a, b));

    unsigned c; cin >> c;
    auto* solution = linearDiofantineEquation(a, b, c);

    if (solution)
        cout << a << " * " << solution->first << " + " << b << " * " << solution->second << " = " << c;
    else
        cout << "There is no solution to " << a <<  " * x1 + " << b << " * x2 = " << c;

    delete solution;
    
    return 0;
}
