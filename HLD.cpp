/*
    Heavy-light tree decomposition 
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e4 + 10;

int tree[4 * MAXN], n;
int tin[MAXN], tout[MAXN], pred[MAXN], h[MAXN], timer = 0;

int getMax(int v, int L, int R, int Lq, int Rq) {
    if (Rq <= L || R <= Lq) {
        return 0;
    }
    if (Lq <= L && R <= Rq) {
        return tree[v];
    }
    int M = (R + L) / 2;
    return max(getMax(2 * v + 1, L, M, Lq, Rq), getMax(2 * v + 2, M, R, Lq, Rq));
}

void update(int v, int L, int R, int val, int pos) {
    if (R - L == 1) {
        tree[v] = val;
        return;
    }
    int M = (R + L) / 2;
    if (pos < M) {
        update(2 * v + 1, L, M, val, pos);
    } else {
        update(2 * v + 2, M, R, val, pos);
    }
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}

int sz[MAXN], head[MAXN];
vector<int> g[MAXN];

void dfs(int v, int p = -1) {
    sz[v] = 1;
    for (auto &u : g[v]) {
        if (u != p) {
            dfs(u, v);
            sz[v] += sz[u];
            if (sz[u] > sz[g[v][0]]) {
                swap(u, g[v][0]);
            }
        }
    }
}

void markTime(int v, int p = -1) {
    tin[v] = timer++;
    update(0, 0, n, h[v], tin[v]);
    for (auto &u : g[v]) {
        if (u != p) {
            pred[u] = v;
            head[u] = (u == g[v][0] ? head[v] : u);
            markTime(u, v);
        }
    }
    tout[v] = timer;
}

bool isPred(int u, int v) {
    return tin[v] <= tin[u] && tin[u] < tout[v];
}

void vertAns(int &u, int &v, int &ans) {
    while (!isPred(v, head[u])) {
        ans = max(ans, getMax(0, 0, n, tin[head[u]], tin[u] + 1));
        u = pred[head[u]];
    }
}

int getAns(int u, int v) {
    int ans = 0;
    vertAns(u, v, ans);
    vertAns(v, u, ans);
    if (!isPred(u, v)) {
        swap(u, v);
    }
    return max(ans, getMax(0, 0, n, tin[v], tin[u] + 1));
}

signed main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0);
    markTime(0);
    int q;
    cin >> q;
    while (q--) {
        char type;
        cin >> type;
        if (type == '!') {
            int v, val;
            cin >> v >> val;
            v--;
            update(0, 0, n, val, tin[v]);
        }
        if (type == '?') {
            int u, v;
            cin >> u >> v;
            u--, v--;
            cout << getAns(u, v) << endl;
        }
    }
}
