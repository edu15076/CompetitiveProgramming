#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

#include <bitset>
#include <sstream>

using namespace std;

int stringToIntBODH(const string& n, int base = 10) {
    return stoi(n, nullptr, base);
}

string intToStringBODH(int n, int base = 10) {
    if (base == 10)
        return to_string(n);
    else if (base == 2)
        return bitset<32>(n).to_string();

    stringstream ss;
    if (base == 8) ss << oct << n; else ss << hex << n;

    return ss.str();
}

uint16_t intForDigit(char digit) {
    uint16_t intDigit = digit - 48;
    if (intDigit > 9)
        return digit - 87;
    return intDigit;
}

char char_for_digit(uint16_t digit) {
    if (digit > 9)
        return digit + 87;
    return digit + 48;
}

int stringToInt(const string& n, unsigned base = 10) {
    int result {0};
    uint64_t basePow {1};
    for (auto it = n.rbegin(); it != n.rend(); ++it, basePow *= base)
        result += intForDigit(*it) * basePow;
    return result;
}

void intToStringRecursive(unsigned n, unsigned base, stringstream& ss) {
    if (not n)
        return;
    intToStringRecursive(n / base, base, ss);
    ss << char_for_digit(n % base);
}

string intToString(unsigned n, unsigned base = 10) {
    if (not n)
        return "0";
    stringstream ss;
    intToStringRecursive(n, base, ss);
    return ss.str();
}

typedef long long ll;

pair<ll, ll> toFraction(double n, unsigned p) {
    const ll tenP = pow(10, p);
    const ll t = (ll) (n * tenP);
    const ll rMdc = gcd(t, tenP);
    return {t / rMdc, tenP / rMdc};
}

long double toLongDouble(double n) {
    return n;
}

int main() {
    int n; cin >> n;
    auto n2 = intToString(n, 2), n8 = intToString(n, 8),
            n10 = intToString(n), n16 = intToString(n, 16);

    cout << "n na base 2: " << n2 << endl;
    cout << "n na base 8: " << n8 << endl;
    cout << "n na base 10: " << n10 << endl;
    cout << "n na base 16: " << n16 << endl;
    cout << endl;

    cout << "n na base 2 convertido para int: " << stringToInt(n2, 2) << endl;
    cout << "n na base 8 convertido para int: " << stringToInt(n8, 8) << endl;
    cout << "n na base 10 convertido para int: " << stringToInt(n10) << endl;
    cout << "n na base 16 convertido para int: " << stringToInt(n16, 16) << endl;

    return 0;
}
