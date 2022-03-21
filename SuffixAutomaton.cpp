#include <bits/stdc++.h>

using namespace std;

#define next next1
#define Node Node1

const int ALF = 30;

struct Node {
    int next[ALF], suff, par;
    long long sum, all_sum;
    Node() {
        memset(next, 255, sizeof(next));
        suff = -1;
        par = -1;
        sum = 0;
        all_sum = 0;
    }

};

vector <Node> nd;

inline int add(int A, const char ch) {
    int B = nd.size();
    nd.emplace_back(Node());
    nd[B].par = A;
    nd[B].suff = 0;
    nd[B].all_sum += nd[A].all_sum;
    for (; A != -1; A = nd[A].suff) {
        if (nd[A].next[ch - 'a'] == -1) {
            nd[A].next[ch - 'a'] = B;
            nd[B].sum += nd[A].sum;
            continue;
        }
        int C = nd[A].next[ch - 'a'];
        if (nd[C].par == A) {
            nd[B].suff = C;
            break;
        }
        int D = nd.size();
        nd.emplace_back(Node());
        for (int c = 0; c < ALF; c++) {
            nd[D].next[c] = nd[C].next[c];
        }
        if (nd[D].par != -1) {
            nd[D].sum -= nd[nd[D].par].sum;
        }
        nd[D].par = A;
        nd[D].suff = nd[C].suff, nd[C].suff = D, nd[B].suff = D;
        for (; A != -1 && nd[A].next[ch - 'a'] == C; A = nd[A].suff) {
            nd[C].sum -= nd[A].sum;
            nd[A].next[ch - 'a'] = D;
            nd[D].sum += nd[A].sum;
        }
        break;
    }
    nd[B].all_sum += nd[B].sum;
    return nd[nd[B].par].next[ch - 'a'];
}

signed main() {
    string s;
    cin >> s;
    int n = s.size();
    int root = 0;
    nd.emplace_back(Node());
    nd[0].sum = 1;
    for (int i = 0; i < n; i++) {
        root = add(root, s[i]);
    }
    cout << nd[root].all_sum;
    return 0;
}
