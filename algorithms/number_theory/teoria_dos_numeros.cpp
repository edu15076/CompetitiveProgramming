#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

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

unsigned phi(unsigned n) {
    auto primeFactorsOfN = factorize(n);
    unsigned result = n;
    for (auto [primeFactor, exponent] : primeFactorsOfN)
        result -= result / primeFactor;
    return result;
}

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
