#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

const double Pi = acos(-1), EPS = 1e-6;

struct Vector {
    int x, y;
    Vector(int _x, int _y) : x(_x), y(_y) {}
    Vector() {}
    double size() {
        return sqrt(x * x + y * y);
    }
};

Vector operator+(const Vector& a, const Vector& b) {
    return Vector(a.x + b.x, a.y + b.y);
}

Vector operator+=(Vector &a, const Vector &b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vector operator*(const Vector& a, double num) {
    return (Vector(a.x * num, a.y * num));
}

Vector operator*(double num, const Vector& a) {
    return (a * num);
}

Vector operator-(const Vector& a, const Vector& b) {
    return a + (-1) * b;
}

Vector operator-=(Vector& a, const Vector& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

long long operator*(const Vector& a, const Vector& b) {
    return 1LL * a.x * b.x + 1LL * a.y * b.y;
}

long long operator%(const Vector& a, const Vector& b) {
    return 1LL * a.x * b.y - 1LL * b.x * a.y;
}

ostream& operator<<(ostream& out, Vector& P) {
    out << P.x << " " << P.y;
    return out;
}

istream& operator>>(istream& in, Vector& p) {
    in >> p.x >> p.y;
    return in;
}

long long sqrLen(const Vector A) {
    return 1LL * A.x * A.x + 1LL * A.y * A.y;
}

std::vector<Vector> makeHull(std::vector<Vector> &p) {
    int n = p.size();
    Vector s = p[0];
    for (int i = 1; i < n; i++) {
        if (p[i].x < s.x || (p[i].x == s.x && p[i].y < s.y)) {
            s = p[i];
        }
    }
    for (auto &x : p) {
        x -= s;
    }
    std::sort(p.begin(), p.end(), [&](Vector A, Vector B) {
            return A % B > 0 || (A % B == 0 && sqrLen(A) < sqrLen(B));
    });
    std::vector<Vector> h;
    h.push_back(p[0]);
    for (int i = 1; i < n; i++) {
        while (h.size() >= 2) {
            Vector a = h[h.size() - 2], b = h[h.size() - 1], c = p[i];
            if ((c - b) % (a - b) > 0) {
                break;
            }
            if ((c - b) % (a - b) == 0 && sqrLen(c - a) < sqrLen(b - a)) {
                break;
            }
            h.pop_back();
        }
        h.push_back(p[i]);
    }
    for (auto &x : h) {
        x += s;
    }
    for (auto &x : p) {
        x += s;
    }
    return h;
}

bool isIn(const std::vector<Vector>& p, const Vector A) {
    int n = p.size();
    if ((p[1] - p[0]) % (A - p[0]) < 0 || (p[n - 1] - p[0]) % (A - p[0]) > 0) {
        return false;
    }
    int L = 1, R = n - 1;
    while (R - L > 1) {
        int M = (R + L) / 2;
        if ((p[M] - p[0]) % (A - p[0]) >= 0) {
            L = M;
        } else {
            R = M;
        }
    }
    return (p[R] - p[L]) % (A - p[L]) >= 0 &&
           (p[0] - p[R]) % (A - p[R]) >= 0 &&
           (p[L] - p[0]) % (A - p[0]) >= 0;
}

struct Line {
    int a, b, c;
    Line() {}
    Line(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
    Vector normal() {
        return Vector(-b, a);
    }
    Vector dir() {
        return Vector(a, b);
    }
};

// angle comparison
bool operator<(const Vector &A, const Vector &B) {
    if (A.y > 0 || (A.y == 0 && A.x > 0)) {
        if (B.y > 0 || (B.y == 0 && B.x > 0)) {
            return A % B > 0;
        }
        return true;
    }
    if (B.y > 0 || (B.y == 0 && B.x > 0)) {
        return false;
    }
    return A % B > 0;
}

std::vector<Vector> MinkovskySum(std::vector<Vector>& p, std::vector<Vector>& h) {
    int id1 = 0, id2 = 0;
    int n = p.size(), m = h.size();
    for (int i = 0; i < n; i++) {
        if (p[i].y < p[id1].y || (p[i].y == p[id1].y && p[i].x < p[id1].x)) {
            id1 = i;
        }
    }
    for (int i = 0; i < m; i++) {
        if (h[i].y < h[id2].y || (h[i].y == h[id2].y && h[i].x < h[id2].x)) {
            id2 = i;
        }
    }
    std::vector<Vector> ans, all;
    ans.push_back(p[id1] + h[id2]);
    for (int i = 0; i < n; i++) {
        all.push_back(p[(i + 1) % n] - p[i]);
    }
    for (int i = 0; i < m; i++) {
        all.push_back(h[(i + 1) % m] - h[i]);
    }
    std::sort(all.begin(), all.end());
    for (auto x : all) {
        ans.push_back(ans.back() + x);
    }
    ans.pop_back();
    return ans;
}

signed main() {
    int n, m, k;
    std::cin >> n;
    std::vector<Vector> A(n);
    for (auto &a : A) {
        cin >> a;
    }
    std::cin >> m;
    std::vector<Vector> B(m);
    for (auto &b : B) {
        std::cin >> b;
    }
    std::cin >> k;
    std::vector<Vector> C(k);
    for (auto &c : C) {
        std::cin >> c;
    }
    std::vector<Vector> h = MinkovskySum(A, B);
    h = MinkovskySum(h, C);
    h = makeHull(h);
    int q;
    std::cin >> q;
    while (q--) {
        Vector A;
        std::cin >> A;
        std::cout << (isIn(h, 3 * A) ? "YES\n" : "NO\n");
    }
}
