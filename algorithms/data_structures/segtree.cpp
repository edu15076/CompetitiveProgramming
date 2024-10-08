#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

template<typename T, typename = typename enable_if<is_arithmetic<T>::value, bool>::type>
class SegTree {
public:
    explicit SegTree(const vector<T>& v) : mValues(v) {
        const size_t n = mValues.size();
        mSeg = vector<size_t>(4 * n, 0);

        // Starts on the root of the SegTree, 1 looking at the entire length of the vector
        mInit(1, 0, n - 1);
    }

    /**
     * Query for the smallest element index on the range that starts on i and ends on j, inclusive.
     * @param i The beginning index of the range, must be greater or equal to j.
     * @param j The ending index of the range.
     * @return The index of the minimum value in the range that starts on i and ends on j.
     */
    size_t query(const size_t& i, const size_t& j) {
        return mQuery(i, j, 1, 0, mValues.size() - 1);
    }

    void update(const size_t& i, const T& val) {
        mValues[i] = val;
        mUpdate(i, val, 1, 0, mValues.size() - 1);
    }

private:
    vector<size_t> mSeg;
    vector<T>& mValues;

    size_t mMinPositionIndexQuery(const size_t i, const size_t j) {
        if (i == -1)
            return j;
        else if (j == -1) // impossible for both to be -1
            return i;
        return mValues[i] <= mValues[j] ? i : j;
    }

    size_t mMinPositionIndex(const size_t i, const size_t j) {
        return mValues[i] <= mValues[j] ? i : j;
    }

    size_t mInit(const size_t pos, const size_t begin, const size_t end) {
        // If begin == end we are on a leaf and the minimum is the leaf itself
        if (begin == end)
            return mSeg[pos] = begin;

        const size_t half {(begin + end) / 2};

        // The pos on the SegTree that is not a leaf should be the minimum of
        return mSeg[pos] = mMinPositionIndex(mInit(2 * pos, begin, half),
                                             mInit(2 * pos + 1, half + 1, end));
    }

    size_t mQuery(const size_t i, const size_t j, const size_t pos, const size_t l, const size_t r) {
        if (j < l || r < i)
            return -1;

        if (i <= l && r <= j)
            return mSeg[pos];

        const size_t half {(l + r) / 2};
        return mMinPositionIndexQuery(mQuery(i, j, 2 * pos, l, half),
                                      mQuery(i, j, 2 * pos + 1, half + 1, r));
    }

    T mUpdate(const size_t i, const size_t pos, const size_t l, const size_t r) {
        if (i < l || r < i)
            return mSeg[pos];

        if (l == r) // l = r = i
            return mSeg[pos] = i;

        const size_t half {(l + r) / 2};
        return mSeg[pos] = mMinPositionIndex(mUpdate(i, 2 * pos, l, half),
                                             mUpdate(i, 2 * pos + 1, half + 1, r));
    }
};

template<typename T, typename = typename enable_if<is_arithmetic<T>::value, bool>::type>
class IterativeSegTree {
public:
    explicit IterativeSegTree(const vector<T>& v) : mValues(v) {
        const size_t n = mValues.size();
        // The greater advantage of the iterative version is the space complexity
        mSeg = vector<size_t>(2 * n);

        // each position on the leafs has a min of itself
        for (size_t i {n}, len = mSeg.size(); i < len; ++i)
            mSeg[i] = i - n;

        // each position that is not a leaf has the min between the two positions under
        for (size_t i {n - 1}; i > 0; --i)
            // equivalente to mSeg[i] = mMinPositionIndex(2 * i, 2 * i + 1)
            mSeg[i] = mMinPositionIndex(i << 1, i << 1 | 1);
    }

    /**
     * Query for the smallest element index on the range that starts on i and ends on j, inclusive.
     * @param i The beginning index of the range, must be greater or equal to j.
     * @param j The ending index of the range.
     * @return The index of the minimum value in the range that starts on i and ends on j.
     */
    size_t query(const size_t& i, const size_t& j) {
        size_t minPosOfRange = -1;

        // Starts on the leafs and ends when getting elements out of range, begin > end, goes to the upper nodes each
        // iteration. In a more formal demonstration it should be proved that it never goes out of range for any size.
        for (size_t begin = i + mValues.size(), end = j + mValues.size() + 1; begin < end; begin >>= 1, end >>= 1) {
            // if odd then it's not on the upper node range, so it should be added to the result
            if (begin & 1)
                minPosOfRange = mMinPositionIndexQuery(minPosOfRange, begin++);
            if (end & 1)
                minPosOfRange = mMinPositionIndexQuery(minPosOfRange, --end);
        }

        return minPosOfRange;
    }

    void update(const size_t& i, const T& val) {
        mValues[i] = val;

        size_t pos = i;

        for (size_t pos = i; pos > 1; pos >>= 1)
            mSeg[pos] = mMinPositionIndex(pos << 1, pos << 1 | 1);
    }

private:
    vector<size_t> mSeg;
    vector<T>& mValues;

    size_t mMinPositionIndexQuery(const size_t i, const size_t j) {
        if (i == -1)
            return j;
        else if (j == -1) // impossible for both to be -1
            return i;
        return mValues[i] <= mValues[j] ? i : j;
    }

    size_t mMinPositionIndex(const size_t i, const size_t j) {
        return mValues[i] <= mValues[j] ? i : j;
    }
};
