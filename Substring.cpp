/*
    Find the longest substring of n string. Time complexity is a very good question, but it is fast, trust me
*/

#include <bits/stdc++.h>

using namespace std;

const int ALF = 26;

struct Node {
    int go[ALF], suff, par;
    int cnt, last_used;
    int max_len, par_len, char_len;
    int why;
    Node() {
        memset(go, 255, sizeof(go));
        suff = par = -1;
        cnt = last_used = 0;
        max_len = 0;
        par_len = char_len = why = -1;
    }
};

vector<Node> nd;
int last = 1;

inline int add(int A, int ch) {
    int B = nd.size();
    nd.push_back(Node());
    nd[B].par = A;
    nd[B].suff = 0;
    for (; A != -1; A = nd[A].suff) {
        if (nd[A].go[ch] == -1) {
            if (nd[A].max_len + 1 > nd[B].max_len) {
                nd[B].max_len = nd[A].max_len + 1;
                nd[B].par_len = A;
                nd[B].why = nd[A].why;
                nd[B].char_len = ch;
            }
            nd[A].go[ch] = B;
            continue;
        }
        int C = nd[A].go[ch];
        if (nd[C].par == A) {
            nd[B].suff = C;
            break;
        }
        int D = nd.size();
        nd.push_back(Node());
        for (int c = 0; c < ALF; c++) {
            nd[D].go[c] = nd[C].go[c];
        }
        nd[D].suff = nd[C].suff;
        nd[C].suff = D;
        nd[B].suff = D;
        nd[D].par = A;
        for (; A != -1 && nd[A].go[ch] == C; A = nd[A].suff) {
            if (nd[A].max_len + 1 > nd[D].max_len) {
                nd[D].max_len = nd[A].max_len + 1;
                nd[D].par_len = A;
                nd[D].char_len = ch;
                nd[D].why = nd[A].why;
            }
            nd[A].go[ch] = D;
        }
        break;
    }
    return nd[nd[B].par].go[ch];
}

void subautomaton(int v) {
    if (nd[v].last_used == last) {
        return;
    }
    nd[v].last_used = last;
    nd[v].cnt++;
    if (nd[v].par != -1) {
        subautomaton(nd[v].par);
    }

    if (nd[v].suff != -1) {
        subautomaton(nd[v].suff);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    nd.push_back(Node());
    int root[n] = {};
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (auto &c : s) {
            root[i] = add(root[i], c - 'a');
        }
    }
    for (int i = 0; i < n; i++) {
        subautomaton(root[i]);
        last++;
    }
    int v = 0;
    for (int i = 0; i < nd.size(); i++) {
        if (nd[i].cnt == n && (nd[i].max_len > nd[v].max_len || (nd[i].max_len == nd[v].max_len && nd[i].why < nd[v].why))) {
            v = i;
        }
    }
    vector<char> ans;
    while (nd[v].char_len != -1) {
        ans.push_back(static_cast<char>(nd[v].char_len + 'a'));
        v = nd[v].par_len;
    }
    reverse(ans.begin(), ans.end());
    for (auto &c : ans) {
        cout << c;
    }
}
