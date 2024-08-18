#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

vector<pair<uint, uint>> select_for_biggest_time(vector<pair<uint, uint>> &events) {
    sort(events.begin(), events.end());
    uint last_end {0};
    vector<pair<uint, uint>> selected_events;

    for (auto [end, start] : events)
        if (start > last_end) {
            selected_events.emplace_back(end, start);
            last_end = end;
        }
    return selected_events;
}
