#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

bool is_subset_sum(const vector<int>& p, int n, int c) {
    vector memo(n + 1, vector<bool>(c + 1, false));
    for (auto &line : memo)
        line[0] = true;

    for (int i {1}; i <= n; i++) {
        for (int j{1}; j <= c; j++)
            if (j < p[i - 1])
                memo[i][j] = memo[i - 1][j];
            else
                memo[i][j] = memo[i - 1][j] or memo[i - 1][j - p[i - 1]];
    }

    return memo[n][c];
}

bool is_subset_sum_memory_save(const vector<int>& p, int n, int c) {
    vector<bool> memo(c + 1, false), memo_before(c + 1, false);
    memo_before[0] = memo[0] = true;

    for (int i {1}; i <= n; i++) {
        for (int j{1}; j <= c; j++)
            if (j < p[i - 1])
                memo[j] = memo_before[j];
            else
                memo[j] = memo_before[j] or memo_before[j - p[i - 1]];
        copy(memo.begin(), memo.end(), memo_before.begin());
        fill(memo.begin(), memo.end(), false);
        memo[0] = true;
    }

    return memo_before[c];
}
