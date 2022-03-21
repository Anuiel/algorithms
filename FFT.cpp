#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")

const double Pi = acos(-1);

struct MyComplex {
    double x, y;
    MyComplex() : x(0), y(0) {}
    MyComplex(double x, double y) : x(x), y(y) {}
    MyComplex(int n) : x(cos(2 * Pi / n)), y(sin(2 * Pi / n)) {}
};

MyComplex operator+(const MyComplex A, const MyComplex B) {
    return MyComplex(A.x + B.x, A.y + B.y);
}

MyComplex operator+=(MyComplex &A, const MyComplex B) {
    A.x += B.x;
    A.y += B.y;
    return A;
}

MyComplex operator-(const MyComplex A, const MyComplex B) {
    return MyComplex(A.x - B.x, A.y - B.y);
}

MyComplex operator*(const MyComplex A, const MyComplex B) {
    return MyComplex(A.x * B.x - A.y * B.y, A.x * B.y + A.y * B.x);
}

MyComplex operator*=(MyComplex &A, const MyComplex B) {
    return A = A * B;
}


void FFT(vector<MyComplex> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        long double ang = 2 * Pi / len * (invert ? -1 : 1);
        MyComplex wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            MyComplex w(1, 0);
            for (int j = 0; j < len / 2; j++) {
                MyComplex u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
}

void multiplication(const vector<int> &A, const vector<int> &B, vector<int> &ans) {
    int n = 1;
    while (n < max(A.size(), B.size())) {
        n <<= 1;
    }
    n <<= 1;
    vector<MyComplex> a, b;
    a.resize(n), b.resize(n);
    for (int i = 0; i < A.size(); i++) {
        a[i] = MyComplex(A[i], 0);
    }
    for (int i = 0; i < B.size(); i++) {
        b[i] = MyComplex(B[i], 0);
    }
    FFT(a, false), FFT(b, false);
    for (int i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    FFT(a, true);
    ans.resize(n);
    for (int i = 0; i < n; i++) {
        ans[i] = (int)(a[i].x / n + 0.5);
    }
}
