#include <bits/stdc++.h>
 
using namespace std;
 
const int ALF = 30;
 
signed main() {
    string s;
    cin >> s;
    for (auto &c : s) {
        c -= ('a' - 1);
    }
    s.push_back(0);
    int n = s.size();
    vector<int> c(n), _c(n), suf(n), _suf(n), st(max(n, ALF + 1));
    for (int i = 0; i < n; i++) {
        c[i] = s[i];
        st[s[i] + 1]++;
        suf[i] = i;
    }
    int sum = 0;
    for (auto &v : st) {
        sum += v;
        v = sum;
    }
    for (int k = 0; k < n; k = (k ? 2 * k : 1)) {
        for (auto v : suf) {
            int pos = (v - k + n) % n;
            _suf[st[c[pos]]++] = pos;
        }
        long long last = -1;
        int type = -1;
        for (int i = 0; i < n; i++) {
            int v = _suf[i];
            if (last != 1LL * c[v] * max(n, ALF + 1) + c[(v + k) % n]) {
                last = 1LL * c[v] * max(n, ALF + 1) + c[(v + k) % n];
                st[++type] = i;
            }
            _c[v] = type;
        }
        swap(_c, c);
        swap(_suf, suf);
    }
    vector<int> lcp(n - 1);
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (c[i] == n - 1) {
            continue;
        }
        int nxt = suf[c[i] + 1];
        while (max(i, nxt) + cur < n && s[i + cur] == s[nxt + cur]) {
            cur++;
        }
        lcp[c[i]] = cur;
        cur = max(0, cur - 1);
    }
    for (auto v : suf) {
        cout << v << " ";
    }
    cout << endl;
    for (auto v : lcp) {
        cout << v << " ";
    }
}
