#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

unsigned lowestPrimeFactor(unsigned n, unsigned startPrime = 2) {
    if (startPrime <= 3) {
        if (not (n & 1))
            return 2;
        if (not (n % 3))
            return 3;
        startPrime = 5;
    }

    for (unsigned i {startPrime}; i * i <= n; i += (i - 3) % 6)
        if (not (n % i))
            return i;
    return n;
}

bool isPrime(unsigned n) {
    return n > 1 and lowestPrimeFactor(n) == n;
}

map<unsigned, uint16_t> factorize(unsigned n) {
    map<unsigned, uint16_t> factorsOfN;
    unsigned lowestPrimeFactorOfN = 2;

    while (n != 1) {
        lowestPrimeFactorOfN = lowestPrimeFactor(n, lowestPrimeFactorOfN);
        factorsOfN[lowestPrimeFactorOfN] = 1;
        n /= lowestPrimeFactorOfN;
        while (not (n % lowestPrimeFactorOfN)) {
            factorsOfN[lowestPrimeFactorOfN]++;
            n /= lowestPrimeFactorOfN;
        }
    }

    return factorsOfN;
}

string primeFactorsToString(map<unsigned, uint16_t> f) {
    std::stringstream s;
    for (auto& [prime, power] : f)
        s << to_string(prime) << (power == 1 ? " * " : ("^" + to_string(power) + " * "));
    std::string str = s.str();
    return str.substr(0, str.length() - 3);
}

/**
 * This function returns the number of positive integers that divide n.
 * @param n
 * @return
 */
unsigned long long numberOfFactors(map<unsigned, uint16_t>& n) {
    unsigned long long numberOfFactors = 1;

    for (auto [primeFactor, exponent] : n)
        numberOfFactors *= exponent + 1;

    return numberOfFactors;
}

unsigned long long numberOfFactors(unsigned n) {
    auto primeFactorsOfN = factorize(n);
    return numberOfFactors(primeFactorsOfN);
}

vector<unsigned> allFactorsOf(map<unsigned, uint16_t>& n, bool sorted = true) {
    vector<unsigned> divisors;
    divisors.reserve(numberOfFactors(n));
    divisors.push_back(1);

    // n will have at most log2(n) prime factors and log2(n) exponents for each factor
    // in that manner, n will have a max of log2(n) * log2(n) factors

    // This outer loop executes at max log2(n) times
    // the entire loop has a complexity of O((log2(n))^4)
    for (auto [p, e] : n) {
        vector<unsigned> divisorsP;

        // This loop executes at max log2(n) times
        for (unsigned i {1}, f {p}; i <= e; ++i, f *= p)
            divisorsP.push_back(f);

        auto factorsCurrSize = divisors.size();

        for (unsigned i {0}; i < factorsCurrSize; ++i) // runs at max log2(n) * log2(n) times
            for (auto d : divisorsP) // at max log2(n)
                divisors.push_back(divisors[i] * d);
    }

    if (sorted) // if this is run then the complexity turns to O(n * log2(n))
        sort(divisors.begin(), divisors.end());

    return divisors;
}

vector<unsigned> allFactorsOf(unsigned n, bool sorted = true) {
    map<unsigned, uint16_t> factorsOfN = factorize(n);
    return allFactorsOf(factorsOfN, sorted);
}

set<unsigned> getUniverseSetForRange(unsigned start, unsigned end) {
    set<unsigned> universeSet;
    for (unsigned i {start}; i <= end; ++i)
        universeSet.insert(i);
    return universeSet;
}

set<unsigned> eratosthenesSieve(unsigned n) {
    set<unsigned> primes = getUniverseSetForRange(2, n);

    for (unsigned i {2}; i <= n; ++i)
        if (primes.contains(i))
            for (unsigned j {i * i}; j <= n; j += i)
                primes.erase(j);
    return primes;
}

int main() { _
    
    return 0;
}
