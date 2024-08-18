#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

// Kadane's algorithm
int largest_contiguous_subarray_sum(const vector<int> &v) {
    int max_sum {INT32_MIN};
    int current_sum {INT32_MIN};
    for (auto item : v) {
        current_sum += item;
        if (current_sum < 0)
            current_sum = item;
        max_sum = max(max_sum, current_sum);
    }

    return max_sum;
}
