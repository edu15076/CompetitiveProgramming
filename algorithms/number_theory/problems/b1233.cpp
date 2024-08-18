// https://www.beecrowd.com.br/judge/pt/problems/view/1233

#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

uint64_t lowestPrimeFactor(uint64_t n, uint64_t startPrime = 2) {
    if (startPrime <= 3) {
        if (not (n & 1))
            return 2;
        if (not (n % 3))
            return 3;
        startPrime = 5;
    }

    for (uint64_t i {startPrime}; i * i <= n; i += (i + 1) % 6 ? 4 : 2)
        if (not (n % i))
            return i;
    return n;
}

vector<uint64_t> factorize(uint64_t n) {
    vector<uint64_t> factorsOfN;
    uint64_t lowestPrimeFactorOfN = 2;

    while (n != 1) {
        lowestPrimeFactorOfN = lowestPrimeFactor(n, lowestPrimeFactorOfN);
        factorsOfN.push_back(lowestPrimeFactorOfN);
        while (not (n % lowestPrimeFactorOfN))
            n /= lowestPrimeFactorOfN;
    }

    return factorsOfN;
}

uint64_t phi(uint64_t n) {
    vector<uint64_t> primeFactorsOfN = factorize(n);
    uint64_t result = n;
    for (auto primeFactor : primeFactorsOfN)
        result -= result / primeFactor;
    return result;
}

int main() { _
    uint64_t n;

    while (cin >> n)
        cout << phi(n) / 2 << endl;

    return 0;
}
