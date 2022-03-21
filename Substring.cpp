/*
    Find the longest substring of n string. Time complexity is a very good question, but it is fast, trust me
*/
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 120, ALF = 26;

int go[MAXN][ALF], suff[MAXN], supersuff[MAXN], last = 0;
bitset<MAXN> terminal;

inline void addString(const string &s) {
    int v = 0;
    for (int i = 0; i < s.size(); i++) {
        if (!go[v][s[i] - 'a']) {
            go[v][s[i] - 'a'] = ++last;
        }
        v = go[v][s[i] - 'a'];
    }
    terminal[v] = true;
}

inline void precalc() {
    deque <int> q;
    q.emplace_back(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        if (v) {
            if (terminal[suff[v]]) {
                supersuff[v] = suff[v];
            } else {
                supersuff[v] = supersuff[suff[v]];
            }
        }
        for (int c = 0; c < ALF; c++) {
            if (!go[v][c]) {
                go[v][c] = go[suff[v]][c];
            } else {
                if (v) {
                    suff[go[v][c]] = go[suff[v]][c];
                }
                q.emplace_back(go[v][c]);
            }
        }
    }
}

typedef vector<vector<int>> matrix;

matrix create(int n, int m) {
    matrix a;
    a.resize(n, vector<int>(m, 0));
    return a;
}

istream &operator>>(istream &in, matrix &a) {
    int n = a.size(), m = a[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            in >> a[i][j];
        }
    }
    return in;
}

ostream &operator<<(ostream &out, const matrix &a) {
    int n = a.size(), m = a[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            out << a[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

const int MOD = 10000;

matrix operator*(matrix &a, const matrix &b) {
    int n = a.size(), m = b[0].size(), p = a[0].size();
    matrix c = create(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                c[i][j] += 1LL * a[i][k] * b[k][j] % MOD;
                c[i][j] %= MOD;
            }
        }
    }
    return c;
}

void operator*=(matrix &a, const matrix &b) {
    a = (a * b);
}

void binPow(matrix &a, long long n) {
    matrix ans = a;
    --n;
    while (n) {
        if (n & 1) {
            ans *= a;
        }
        a *= a;
        n >>= 1;
    }
    a = ans;
}

int binPow(int a, long long n, int m = MOD) {
    if (n == 0) {
        return 1;
    }
    int ans = binPow(a, n / 2, m);
    if (n % 2 == 0) {
        return ans * ans % m;
    } else {
        return (ans * ans % m) * a % m;
    }
}

signed main() {
    #ifndef LOCAL
    freopen("strings.in", "r", stdin);
    freopen("strings.out", "w", stdout);
    #endif // LOCAL
    int sz, n;
    cin >> sz >> n;
    while (n--) {
        string s;
        cin >> s;
        addString(s);
    }
    precalc();
    matrix base = create(last + 1, last + 1);
    for (int v = 0; v <= last; v++) {
        if (terminal[v] || supersuff[v]) {
            continue;
        }
        for (int c = 0; c < ALF; c++) {
            if (!terminal[go[v][c]] && !supersuff[go[v][c]])
                base[v][go[v][c]]++;
        }
    }
    binPow(base, sz);
    int ans = binPow(ALF, sz);
    for (int v = 0; v <= last; v++) {
        if (!terminal[v]) {
            ans += MOD - base[0][v];
            ans %= MOD;
        }
    }
    cout << ans;
}
