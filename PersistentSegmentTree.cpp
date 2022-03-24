#include <bits/stdc++.h>

using namespace std;

const int MAXN = 450000 + 1, MOD = 1e9, MAXM = 1e7;

int last_nd = 0;

struct Node {
    int sum, left, right;
    Node() : sum(0), left(-1), right(-1) {}
};

Node nd[MAXM];
int roots[MAXN];

int build(int L, int R) {
    int v = last_nd++;
    if (R - L > 1) {
        int M = ((R + L) >> 1);
        nd[v].left = build(L, M);
        nd[v].right = build(M, R);
        nd[v].sum = nd[nd[v].left].sum + nd[nd[v].right].sum;
    } else {
        nd[v].sum = 0;
    }
    return v;
}

int update(int v, int L, int R, int index, int val) {
    if (index < L || R <= index) {
        return v;
    }
    nd[last_nd++] = nd[v];
    int u = last_nd - 1;
    nd[u].sum += val;
    if (R - L > 1) {
        int M = ((L + R) >> 1);
        if (index < M) {
            nd[u].left = update(nd[u].left, L, M, index, val);
        } else {
            nd[u].right = update(nd[u].right, M, R, index, val);
        }
    }
    return u;
}

int getSum(int v, int L, int R, int Lq, int Rq) {
    if (Rq <= L || R <= Lq) {
        return 0;
    }
    if (Lq <= L && R <= Rq) {
        return nd[v].sum;
    }
    int M = (R + L) / 2;
    return getSum(nd[v].left, L, M, Lq, Rq) + getSum(nd[v].right, M, R, Lq, Rq);
}

inline int get_k_th(int Lr, int Rr, int L, int R, int k) {
    while (R - L > 1) {
        int M = (R + L) / 2, sum = nd[nd[Rr].left].sum - nd[nd[Lr].left].sum;
        if (k < sum) {
            Lr = nd[Lr].left;
            Rr = nd[Rr].left;
            R = M;
        } else {
            Lr = nd[Lr].right;
            Rr = nd[Rr].right;
            L = M;
            k -= sum;
        }
    }
    return L;
}

signed main() {
    int n;
    cin >> n;
    int t, s, a[n];
    cin >> a[0] >> t >> s;
    int b[n] = {a[0]};
    for (int i = 1; i < n; i++) {
        a[i] = (1LL * a[i - 1] * t % MOD + s) % MOD;
        b[i] = a[i];
    }
    sort(b, b + n);
    unordered_map<int, int> toSmall, toBig;
    int last = -1, p = 0;
    for (int i = 0; i < n; i++)  {
        if (b[i] != last) {
            last = b[i];
            toSmall[b[i]] = p;
            toBig[p] = b[i];
            p++;
        }
    }
    roots[0] = build(0, n);
    for (int i = 0; i < n; i++) {
        roots[i + 1] = update(roots[i], 0, n, toSmall[a[i]], 1);
    }
    int m;
    cin >> m;
    long long ans = 0;
    for (int __ = 0; __ < m; __++) {
        int g;
        cin >> g;
        int x, tx, sx, y, ty, sy, k, tk, sk;
        cin >> x >> tx >> sx >> y >> ty >> sy >> k >> tk >> sk;
        for (int _ = 0; _ < g; _++) {
            int i = x, j = y;
            if (x > y) {
                swap(i, j);
            }
            ans += toBig[get_k_th(roots[i - 1], roots[j], 0, n, k - 1)];
            x = (1LL * (i - 1) * tx + sx) % n + 1;
            y = (1LL * (j - 1) * ty + sy) % n + 1;
            i = x, j = y;
            if (x > y) {
                swap(i, j);
            }
            k = (1LL * (k - 1) * tk + sk) % (j - i + 1) + 1;
        }
    }
    cout << ans;
}
