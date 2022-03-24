#include <vector>
#include <iostream>
#include <deque>
#include <cstring>

const int MAXN = 500 + 10, INF = 1e9;

struct Edge {
    int to, capacity, flow;
    Edge(int to, int capacity) : to(to), capacity(capacity), flow(0) {}
    int get_capacity() {
        return capacity - flow;
    }
};

std::vector<int> g[MAXN];
std::vector<Edge> edges;
int S, T;
int ptr[MAXN], dist[MAXN];
int M;

int dfs(int v, int min_capacity) {
    if (v == T) {
        return min_capacity;
    }
    while (ptr[v] < g[v].size()) {
        int id = g[v][ptr[v]];
        ptr[v]++;
        if (edges[id].get_capacity() < M) {
            continue;
        }
        if (dist[v] + 1 == dist[edges[id].to]) {
            int x = dfs(edges[id].to, std::min(edges[id].get_capacity(), min_capacity));
            if (x) {
                ptr[v]--;
                edges[id].flow += x;
                edges[id ^ 1].flow -= x;
                return x;
            }
        }
    }
    return 0;
}

bool bfs() {
    std::fill(dist, dist + MAXN, INF);
    dist[S] = 0;
    std::deque<int> q;
    q.push_back(S);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (auto id : g[v]) {
            if (edges[id].get_capacity() < M) {
                continue;
            }
            if (dist[edges[id].to] == INF) {
                dist[edges[id].to] = dist[v] + 1;
                q.push_back(edges[id].to);
            }
        }
    }
    return dist[T] != INF;
}

long long findFlow() {
    long long maxFlow = 0;
    for (M = (1 << 15); M >= 1; M >>= 1) {
        while (bfs()) {
            int flow;
            memset(ptr, 0, sizeof(ptr));
            while (flow = dfs(S, INF)) {
                maxFlow += flow;
            }
        }
    }
    return maxFlow;
}

void addEdge(int u, int v, int w) {
    g[u].push_back(edges.size());
    edges.push_back(Edge(v, w));
    g[v].push_back(edges.size());
    edges.push_back(Edge(u, 0));
}

int main() {
    int n, m;
    std::cin >> n >> m;
    S = 0, T = n - 1;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--, v--;
        addEdge(u, v, w);
    }
    std::cout << findFlow();
}
