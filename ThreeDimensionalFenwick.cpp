#include <iostream>

using namespace std;

const int MAXN = 130;
int f[MAXN][MAXN][MAXN];

/*
Three-dimensional Fenwick's tree
indexation from 1 to n
*/

void update(int x, int y, int z, int val) {
    for (int i = x; i < MAXN; i += (i & -i)) {
        for (int j = y; j < MAXN; j += (j & -j)) {
            for (int k = z; k < MAXN; k += (k & -k))
                f[i][j][k] += val;
        }
    }
}

// from [0, x]
long long get(int x, int y, int z) {
    long long res = 0;
    for (int i = x; i > 0; i -= (i & -i)) {
        for (int j = y; j > 0; j -= (j & -j)) {
            for (int k = z; k > 0; k -= (k & -k))
                res += f[i][j][k];
        }
    }
    return res;
}

long long getAns(int x1, int y1, int z1, int x2, int y2, int z2) {
    return get(x2, y2, z2) - get(x1 - 1, y2, z2) - get(x2, y1 - 1, z2) - get(x2, y2, z1 - 1)
         + get(x2, y1 - 1, z1 - 1) + get(x1 - 1, y2, z1 - 1) + get(x1 - 1, y1 - 1, z2)
         - get(x1 - 1, y1 - 1, z1 - 1);
}

int main() {
    int n;
    cin >> n;
    while (true) {
        char type;
        cin >> type;
        if (type == '1') {
            int x, y, z, val;
            cin >> x >> y >> z >> val;
            update(x + 1, y + 1, z + 1, val);
        } else if (type == '2') {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << getAns(x1 + 1, y1 + 1, z1 + 1, x2 + 1, y2 + 1, z2 + 1) << endl;
        } else {
            break;
        }
    }
}
