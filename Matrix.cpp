#include <bits/stdc++.h>

using namespace std;

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

const int MOD = 1e9 + 7;

matrix operator*(matrix &a, const matrix &b) {
    int n = a.size(), m = b[0].size(), p = a[0].size();
    matrix c = create(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                c[i][j] += 1LL * a[i][k] * b[k][j] % MOD;
                if (c[i][j] >= MOD) {
                    c[i][j] -= MOD;
                }
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


signed main() {
    freopen("fibonacci.in", "r", stdin);
    freopen("fibonacci.out", "w", stdout);
    int a, b, c, d, e;
    long long n;
    cin >> a >> b >> c >> d >> e >> n;
    c *= 2;
    matrix base = {{a, b, c, d, e},
                   {1, 0, 0, 0, 0},
                   {0, 0, 2, 0, 0},
                   {0, 0, 0, 1, 1},
                   {0, 0, 0, 0, 1}};
    if (n == 1 | n == 2) {
        cout << 1;
        return 0;
    }
    binPow(base, n - 2);
    matrix e0 = {{1}, {1}, {4}, {3}, {1}};
    base *= e0;
    cout << base[0][0];
}
