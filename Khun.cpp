#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250;

vector<int> g[MAXN];
bitset<MAXN> used;
int right_pair[MAXN], left_pair[MAXN];

bool khun(int v) {
    used[v] = true;
    for (auto &u : g[v]) {
        if (left_pair[u] == -1) {
            right_pair[v] = u;
            left_pair[u] = v;
            return true;
        }
    }
    for (auto &u : g[v]) {
        if (!used[left_pair[u]] && khun(left_pair[u])) {
            right_pair[v] = u;
            left_pair[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    memset(right_pair, 255, sizeof(right_pair));
    memset(left_pair, 255, sizeof(left_pair));
    for (int i = 0; i < n; i++) {
        int v;
        while (cin >> v && v) {
            g[i].emplace_back(v - 1);
        }
    }
    bool run = true;
    int ans = 0;
    while (run) {
        run = false;
        used.reset();
        for (int i = 0; i < n; i++) {
            if (!used[i] && right_pair[i] == -1 && khun(i)) {
                ans++;
                run = true;
            }
        }
    }
    cout << ans;
    return 0;
}
