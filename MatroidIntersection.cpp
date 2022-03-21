/*
    The hardest algo I've ever wrote
*/

#include <bits/stdc++.h>

#define rank rank228
typedef long long ll;

const short MAXN = 800;
const int MAXLEN = 1e8;
const ll INF = 1e15;

struct edge {
    short v1, u1, v2, u2;
    int wt;
};

short parent[2 * MAXN], rank[2 * MAXN];

inline void createSet(short v) {
    parent[v] = v;
    rank[v] = 0;
}

inline short getId(short v) {
    if (parent[v] == v) {
        return v;
    }
    return parent[v] = getId(parent[v]);
}

inline void mergeSet(short a, short b) {
    a = getId(a), b = getId(b);
    if (a == b) {
        return;
    }
    if (rank[a] < rank[b]) {
        std::swap(a, b);
    }
    parent[b] = a;
    if (rank[a] == rank[b]) {
        rank[a]++;
    }
}

std::pair<short, short> g[MAXN * MAXN];
int ptr1 = 0;

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    short n, m;
    std::cin >> n >> m;
    edge all[m];
    for (short i = 0; i < m; i++) {
        std::cin >> all[i].v1 >> all[i].u1 >> all[i].v2 >> all[i].u2 >> all[i].wt;
        all[i].v1--, all[i].u1--, all[i].v2--, all[i].u2--;
    }
    std::bitset<MAXN> good;
    good.reset();
    for (short step = 0; step < m; step++) {
        ptr1 = 0;
        /// std::vector<std::pair<short, short>> g;
        for (short i = 0; i < m; i++) {
            if (!good[i]) continue;
            std::iota(parent, parent + MAXN * 2, 0);
            memset(rank, 0, sizeof(rank));
            for (short k = 0; k < m; k++) {
                if (good[k] && k != i) {
                    mergeSet(all[k].v1, all[k].u1);
                    mergeSet(all[k].v2 + MAXN, all[k].u2 + MAXN);
                }
            }
            for (short j = 0; j < m; j++) {
                if (!good[j]) {
                    if (getId(all[j].v1) != getId(all[j].u1)) {
                        ///g.push_back({i, j});
                        g[ptr1++] = std::make_pair(i, j);
                    }
                    if (getId(all[j].v2 + MAXN) != getId(all[j].u2 + MAXN)) {
                        ///g.push_back({j, i});
                        g[ptr1++] = std::make_pair(j, i);
                    }
                }
            }
        }
        std::iota(parent, parent + MAXN * 2, 0);
        memset(rank, 0, sizeof(rank));
        for (short k = 0; k < m; k++) {
            if (good[k]) {
                mergeSet(all[k].v1, all[k].u1);
                mergeSet(all[k].v2 + MAXN, all[k].u2 + MAXN);
            }
        }
        std::vector<short> Y1, Y2;
        for (short i = 0; i < m; i++) {
            if (getId(all[i].v1) != getId(all[i].u1)) {
                Y1.emplace_back(i);
            }
            if (getId(all[i].v2 + MAXN) != getId(all[i].u2 + MAXN)) {
                Y2.emplace_back(i);
            }
        }
        std::vector<std::pair<ll, int>> d(m, {-INF, MAXLEN});
        for (auto &y : Y1) {
            d[y] = {all[y].wt, 0};
        }
        short par[m];
        memset(par, 255, sizeof(par));
        bool flag = false;
        for (short i = 0; i < n; i++) {
            for (int k = 0; k < ptr1; k++) {
                short v = g[k].first, u = g[k].second;
                ll cost = all[u].wt;
                if (good[u]) {
                    cost *= -1;
                }
                if (d[v] != std::make_pair(-INF, MAXLEN) && d[u] < std::make_pair(cost + d[v].first, d[v].second - 1)) {
                    d[u] = {cost + d[v].first, d[v].second - 1};
                    par[u] = v;
                    flag = true;
                }
            }
            if (!flag)
                break;
            flag = false;
        }
        short maxId = -1;
        for (auto &y : Y2) {
            if (d[y].first != -INF && (maxId == -1 || d[maxId] < d[y])) {
                maxId = y;
            }
        }
        if (maxId == -1) {
            while (step++ < m) {
                std::cout << "Impossible\n";
            }
            return 0;
        }
        while (maxId != -1) {
            good[maxId].flip();
            maxId = par[maxId];
        }
        long long sum = 0;
        for (short v = 0; v < m; v++) {
            if (good[v]) {
                sum += all[v].wt;
            }
        }
        std::cout << sum << "\n";
    }
}
