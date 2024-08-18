#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

template<typename T>
class SparseTable {
public:
    explicit SparseTable(vector<T>& v) : mValues(v) {
        size_t n = mValues.size();

        mSparseTable.emplace_back(n);

        // o minimo de toda posição unitária é ela mesma
        for (size_t i {0}; i < n; ++i)
            mSparseTable[0][i] = i;

        for (uint8_t j {1}; 1 << j <= n; ++j) { // 2^j == 1 << j
            const size_t lineSize = n - (1 << j) + 1;
            // cria todas as log2(n) colunas
            mSparseTable.emplace_back(lineSize);
            for (size_t i {0}; i < lineSize; ++i) { // percorre todos as linhas tais que n - i >= 2^j
                const size_t secondHalf = i + (1 << (j - 1));
                // verifica se o valor da primeira metade de v[i:i + 2^j] é menor ou igual do que o valor da segunda
                // metade, se for salvamos o valor da primeira metade, senão o da segunda
                mSparseTable[j][i] = mValues[mSparseTable[j - 1][i]] <= mValues[mSparseTable[j - 1][secondHalf]] ?
                                     mSparseTable[j - 1][i] : mSparseTable[j - 1][secondHalf];
            }
        }
    }

    size_t query(const size_t& i, const size_t& j) {
        const auto k = static_cast<size_t>(floor(log(j - i + 1) / log(2)));

        return mValues[mSparseTable[k][i]] <= mValues[mSparseTable[k][j - (1 << k) + 1]] ?
               mSparseTable[k][i] : mSparseTable[k][j - (1 << k) + 1];
    }

    void update(const size_t& index, const T& value) { // O(n)
        const size_t n = mValues.size();
        mValues[index] = value;

        for (uint8_t j {1}; 1 << j <= n; ++j) {
            const size_t lineSize = n - (1 << j) + 1;
            const size_t start = lineSize < n - index ? 0 : index + lineSize - n,
                    end = index < lineSize ? index + 1 : lineSize;

            for (size_t i {start}; i < end; ++i) {
                const size_t secondHalf = i + (1 << (j - 1));
                mSparseTable[j][i] = mMinPositionIndex(mSparseTable[j - 1][i], mSparseTable[j - 1][secondHalf]);
            }
        }
    }

    string toString() {
        stringstream ss;
        for (auto& column : mSparseTable) {
            for_each(column.begin(), column.end() - 1, [&ss](auto item) {
                ss << item << " ";
            });
            ss << *(column.end() - 1) << endl;
        }
        return ss.str();
    }

private:
    vector<vector<size_t>> mSparseTable;
    vector<T>& mValues;

    size_t mMinPositionIndex(const size_t& i, const size_t& j) {
        return mValues[i] <= mValues[j] ? i : j;
    }
};
