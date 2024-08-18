// https://www.beecrowd.com.br/judge/pt/problems/view/1193

#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

unsigned stringToIntBODH(const string& n, unsigned base = 10) {
    return stoi(n, nullptr, base);
}

string intToStringBODH(unsigned n, unsigned base = 10) {
    if (base == 10)
        return to_string(n);
    else if (base == 2) {
        string bitStr = bitset<32>(n).to_string();
        return bitStr.substr(bitStr.length() - log2(n));
    }

    stringstream ss;
    if (base == 8) ss << oct << n; else ss << hex << n;

    return ss.str();
}

int main() { _
    unsigned n; cin >> n;
    map<uint16_t, string> bases {{2, "bin"},
                                 {10, "dec"},
                                 {16, "hex"}};
    vector<uint16_t> orderedBases {10, 16, 2};

    for (unsigned i {1}; i <= n; ++i) {
        string x, y; cin >> x >> y;
        unsigned base;
        if (y == "bin")
            base = 2;
        else if (y == "dec")
            base = 10;
        else
            base = 16;

        unsigned xInteger = stringToIntBODH(x, base);

        cout << "Case " << i << ":" << endl;

        for (auto b : orderedBases)
            if (base != b)
                cout << intToStringBODH(xInteger, b) << " " << bases[b] << endl;
        cout << endl;
    }

    return 0;
}
