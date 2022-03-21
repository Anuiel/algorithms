#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int to, capacity, flow, cost;
    Edge(int to, int capacity, int cost) : to(to), capacity(capacity), flow(0), cost(cost) {}
    int get_capacity() {
        return capacity - flow;
    }
};

const int MAXN = 200, INF = 1e9;
vector<int> g[MAXN];
vector<Edge> edges;
int dist[MAXN], p[MAXN], parent[MAXN];
int S, T, n;
bitset<MAXN> used;

bool dijkstra() {
    used.reset();
    fill(dist, dist + MAXN, INF);
    dist[S] = 0;
    set<pair<int, int>> pepega;
    pepega.insert({0, S});
    while (!pepega.empty()) {
        int v = pepega.begin()->second;
        pepega.erase(pepega.begin());
        for (auto id : g[v]) {
            int u = edges[id].to;
            int w = edges[id].cost + p[u] - p[v];
            if (edges[id].get_capacity() && dist[u] > dist[v] + w) {
                pepega.erase({dist[u], u});
                dist[u] = dist[v] + w;
                parent[u] = id ^ 1;
                pepega.insert({dist[u], u});
            }
        }
    }
    return dist[T] != INF;
}

long long findFlow() {
    long long maxFlow = 0, allCost = 0;
    while (dijkstra()) {
        memcpy(p, dist, sizeof(dist));
        int min_capacity = INF;
        for (int v = T; v != S; v = edges[parent[v]].to) {
            min_capacity = min(min_capacity, edges[parent[v] ^ 1].get_capacity());
        }
        maxFlow += min_capacity;
        for (int v = T; v != S; v = edges[parent[v]].to) {
            edges[parent[v] ^ 1].flow += min_capacity;
            edges[parent[v]].flow -= min_capacity;
            allCost += 1LL * min_capacity * edges[parent[v] ^ 1].cost;
        }
    }
    return allCost;
}

void addEdge(int u, int v, int cap, int cost) {
    g[u].push_back(edges.size());
    edges.push_back(Edge(v, cap, cost));
    g[v].push_back(edges.size());
    edges.push_back(Edge(u, 0, -cost));
}

void fordBellman() {
    fill(dist, dist + MAXN, INF);
    dist[S] = 0;
    while (true) {
        bool kavo = false;
        for (int id = 0; id < edges.size(); id++) {
            if (edges[id].get_capacity()) {
                int u = edges[id].to, v = edges[id ^ 1].to, w = edges[id].cost;
                if (dist[v] != INF && dist[u] > dist[v] + w) {
                    dist[u] = dist[v] + w;
                    kavo = true;
                }
            }
        }
        if (!kavo) {
            break;
        }
    }
}

signed main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, cap, cost;
        cin >> u >> v >> cap >> cost;
        addEdge(u, v, cap, cost);
    }
    S = 1, T = n;
    fordBellman();
    cout << findFlow();
}
