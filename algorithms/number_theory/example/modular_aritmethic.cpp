#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

unsigned phiUnoptimized(unsigned n) {
    unsigned result {1};

    for (int i {2}; i < n; ++i)
        if (gcd(n, i) == 1)
            ++result;
    return result;
}

unsigned lowestPrimeFactor(unsigned n, unsigned startPrime = 2) {
    if (startPrime <= 3) {
        if (not (n & 1))
            return 2;
        if (not (n % 3))
            return 3;
        startPrime = 5;
    }

    for (unsigned i {startPrime}; i * i <= n; i += (i + 1) % 6 ? 4 : 2)
        if (not (n % i))
            return i;
    return n;
}

vector<unsigned> factorize(unsigned n) {
    vector<unsigned> factorsOfN;
    unsigned lowestPrimeFactorOfN = 2;

    while (n != 1) {
        lowestPrimeFactorOfN = lowestPrimeFactor(n, lowestPrimeFactorOfN);
        factorsOfN.push_back(lowestPrimeFactorOfN);
        while (not (n % lowestPrimeFactorOfN))
            n /= lowestPrimeFactorOfN;
    }

    return factorsOfN;
}

unsigned phi(unsigned n) {
    // vector<unsigned> factorize(unsigned);
    vector<unsigned> primeFactorsOfN = factorize(n);
    unsigned result = n;
    for (auto primeFactor : primeFactorsOfN)
        result -= result / primeFactor;
    return result;
}

int main() { _
    unsigned n; cin >> n;
    dbg(phi(n));
    
    return 0;
}
