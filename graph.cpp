

// ---------- DFS ----------

void dfs(int u) {
    vis[u] = true;

    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}


// ---------- BFS ----------

vector<int> bfs(int src, int n) {
    vector<int> dist(n, -1);
    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return dist;
}


// Bipartite Graph - BFS
// color[i] = -1 -> uncolored
// color[i] = 0/1 -> two different groups
// parameters: no.of nodes in graph, adjacency list

bool isBipartite(int n, vector<vector<int>>& adj) {
    vector<int> color(n, -1);

    for (int start = 0; start < n; start++) {
        if (color[start] != -1)
            continue;

        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    q.push(v);
                }
                else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }

    return true;
}


// ==================== CYCLE DETECTION ====================

// ---------- Undirected Graph (DFS) ----------

bool dfsUndirected(int u, int parent, vector<vector<int>>& adj,
                   vector<bool>& vis) {
    vis[u] = true;

    for (int v : adj[u]) {
        if (!vis[v]) {
            if (dfsUndirected(v, u, adj, vis))
                return true;
        }
        else if (v != parent) {
            return true;
        }
    }

    return false;
}

bool hasCycleUndirected(int n, vector<vector<int>>& adj) {
    vector<bool> vis(n, false);

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (dfsUndirected(i, -1, adj, vis))
                return true;
        }
    }

    return false;
}


// ---------- Undirected Graph (BFS) ----------

bool hasCycleUndirectedBFS(int n, vector<vector<int>>& adj) {
    vector<bool> vis(n, false);

    for (int start = 0; start < n; start++) {
        if (vis[start])
            continue;

        queue<pair<int, int>> q;
        q.push({start, -1});
        vis[start] = true;

        while (!q.empty()) {
            auto [u, parent] = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push({v, u});
                }
                else if (v != parent) {
                    return true;
                }
            }
        }
    }

    return false;
}


// ---------- Directed Graph (DFS) ----------
// state:
// 0 = unvisited
// 1 = currently in DFS path
// 2 = completely processed

bool dfsDirected(int u, vector<vector<int>>& adj,
                 vector<int>& state) {
    state[u] = 1;

    for (int v : adj[u]) {
        if (state[v] == 1) {
            return true; // back edge -> cycle
        }

        if (state[v] == 0) {
            if (dfsDirected(v, adj, state))
                return true;
        }
    }

    state[u] = 2;
    return false;
}

bool hasCycleDirected(int n, vector<vector<int>>& adj) {
    vector<int> state(n, 0);

    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            if (dfsDirected(i, adj, state))
                return true;
        }
    }

    return false;
}


// ---------- Directed Graph (Kahn's Algorithm) ----------
// If processed vertices < n -> cycle exists

bool hasCycleDirectedBFS(int n, vector<vector<int>>& adj) {
    vector<int> indegree(n, 0);

    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int cnt = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;

        for (int v : adj[u]) {
            indegree[v]--;

            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return cnt != n;
}


// ==================== TOPOLOGICAL SORT ====================

// ---------- DFS ----------

bool dfs(int u, vector<vector<int>>& adj, vector<int>& state,
         vector<int>& topo) {
    state[u] = 1;

    for (int v : adj[u]) {
        if (state[v] == 1) return false; // cycle

        if (state[v] == 0) {
            if (!dfs(v, adj, state, topo))
                return false;
        }
    }

    state[u] = 2;
    topo.push_back(u);

    return true;
}

vector<int> topoSortDFS(int n, vector<vector<int>>& adj) {
    vector<int> state(n, 0);
    vector<int> topo;

    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            if (!dfs(i, adj, state, topo))
                return {}; // cycle
        }
    }

    reverse(topo.begin(), topo.end());
    return topo;
}


// ---------- Kahn's Algorithm (BFS) ----------

vector<int> topoSortBFS(int n, vector<vector<int>>& adj) {
    vector<int> indegree(n, 0);

    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    vector<int> topo;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        topo.push_back(u);

        for (int v : adj[u]) {
            indegree[v]--;

            if (indegree[v] == 0)
                q.push(v);
        }
    }

    if ((int)topo.size() != n)
        return {}; // cycle

    return topo;
}


// ==================== DIJKSTRA ====================
// For graphs with NON-NEGATIVE edge weights.
//
// adj[u] = {{v, weight}, ...}

vector<long long> dijkstra(int src, int n,
                           vector<vector<pair<int, int>>>& adj) {
    const long long INF = 4e18;

    vector<long long> dist(n, INF);

    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u])
            continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}



// ==================== DSU ====================

struct DSU {
    vector<int> parent, rank, sz;

    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        sz.assign(n, 1);

        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]); // Path compression
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        // Union by rank
        if (rank[a] < rank[b])
            swap(a, b);

        parent[b] = a;

        // Update size
        sz[a] += sz[b];

        // Update rank
        if (rank[a] == rank[b])
            rank[a]++;

        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
};


// ==================== KRUSKAL MST ====================
// edges = {weight, u, v}

struct Edge {
    int u, v, w;

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

pair<long long, vector<Edge>> kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());

    DSU dsu(n);

    long long mstWeight = 0;
    vector<Edge> mst;

    for (auto e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mstWeight += e.w;
            mst.push_back(e);

            if ((int)mst.size() == n - 1)
                break;
        }
    }

    // Disconnected graph -> MST doesn't exist
    if ((int)mst.size() != n - 1)
        return {-1, {}};

    return {mstWeight, mst};
}


// ==================== PRIM'S MST ====================
// adj[u] = {{v, weight}, ...}

pair<long long, vector<Edge>> prim(int n,
                                   vector<vector<pair<int, int>>>& adj) {
    const long long INF = 4e18;

    vector<long long> key(n, INF);
    vector<int> parent(n, -1);
    vector<bool> used(n, false);

    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > pq;

    key[0] = 0;
    pq.push({0, 0});

    long long mstWeight = 0;
    vector<Edge> mst;

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (used[u])
            continue;

        used[u] = true;
        mstWeight += w;

        if (parent[u] != -1) {
            mst.push_back({parent[u], u, (int)w});
        }

        for (auto [v, weight] : adj[u]) {
            if (!used[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    // Disconnected graph -> MST doesn't exist
    if ((int)mst.size() != n - 1)
        return {-1, {}};

    return {mstWeight, mst};
}



// ==================== FLOYD-WARSHALL ====================
// Usage: dist[u][v] = edge weight, then run floydWarshall(dist, n).
// Supports negative edges, but not negative cycles.

void floydWarshall(vector<vector<long long>>& dist, int n) {
    const long long INF = 4e18;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF)
                continue;

            for (int j = 0; j < n; j++) {
                if (dist[k][j] == INF)
                    continue;

                dist[i][j] = min(dist[i][j],
                                 dist[i][k] + dist[k][j]);
            }
        }
    }
}


// ==================== BELLMAN-FORD ====================
// Usage: edges = {{u,v,w},...}, then call bellmanFord(src,n,edges).
// Supports negative edges; dist[v] = -1e18 means reachable negative cycle.

struct Edge {
    int u, v;
    long long w;
};

vector<long long> bellmanFord(int src, int n, vector<Edge>& edges) {
    const long long INF = 4e18;

    vector<long long> dist(n, INF);
    dist[src] = 0;

    for (int i = 1; i <= n - 1; i++) {
        bool changed = false;

        for (auto [u, v, w] : edges) {
            if (dist[u] == INF)
                continue;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                changed = true;
            }
        }

        if (!changed)
            break;
    }

    // Negative cycle reachable from src
    for (auto [u, v, w] : edges) {
        if (dist[u] != INF && dist[v] > dist[u] + w) {
            dist[v] = -INF;
        }
    }

    return dist;
}


// ==================== KOSARAJU SCC + CONDENSATION GRAPH ====================
// 1-indexed graph
// Returns:
//   first  -> SCCs
//   second -> condensation graph
//
// roots[u] = representative (minimum vertex) of u's SCC
// condes[root1] contains root2 if there is an edge between SCCs

pair<vector<vector<int>>, vector<vector<int>>> kosa(
    vector<vector<int>>& graph, int n) {

    vector<int> vis(n + 1, 0);
    vector<int> order;

    auto dfs1 = [&](auto&& dfs1, int u) -> void {
        vis[u] = 1;

        for (int v : graph[u]) {
            if (!vis[v]) {
                dfs1(dfs1, v);
            }
        }

        order.push_back(u);
    };

    // DFS on original graph
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs1(dfs1, i);
        }
    }

    reverse(order.begin(), order.end());

    // Reverse graph
    vector<vector<int>> rev(n + 1);

    for (int u = 1; u <= n; u++) {
        for (int v : graph[u]) {
            rev[v].push_back(u);
        }
    }

    fill(vis.begin(), vis.end(), 0);

    vector<vector<int>> compo;
    vector<int> roots(n + 1);

    auto dfs2 = [&](auto&& dfs2, int u) -> void {
        vis[u] = 1;
        compo.back().push_back(u);

        for (int v : rev[u]) {
            if (!vis[v]) {
                dfs2(dfs2, v);
            }
        }
    };

    // DFS on reversed graph
    for (int u : order) {
        if (!vis[u]) {
            compo.push_back({});

            dfs2(dfs2, u);

            int root = *min_element(
                compo.back().begin(),
                compo.back().end()
            );

            for (int v : compo.back()) {
                roots[v] = root;
            }
        }
    }

    // Condensation graph
    vector<vector<int>> condes(n + 1);

    for (int u = 1; u <= n; u++) {
        for (int v : graph[u]) {
            if (roots[u] != roots[v]) {
                condes[roots[u]].push_back(roots[v]);
            }
        }
    }

    return {compo, condes};
}



// ==================== BRIDGES ====================
// Usage: build adj, then call findBridges(n, adj).

vector<int> tin, low;
vector<pair<int, int>> bridges;
int timer;

void dfsBridge(int u, int p, vector<vector<int>>& adj) {
    tin[u] = low[u] = timer++;

    for (int v : adj[u]) {
        if (v == p)
            continue;

        if (tin[v] != -1) {
            low[u] = min(low[u], tin[v]);
        }
        else {
            dfsBridge(v, u, adj);

            low[u] = min(low[u], low[v]);

            if (low[v] > tin[u])
                bridges.push_back({u, v});
        }
    }
}

vector<pair<int, int>> findBridges(
    int n, vector<vector<int>>& adj) {

    tin.assign(n + 1, -1);
    low.assign(n + 1, -1);
    bridges.clear();
    timer = 0;

    for (int i = 1; i <= n; i++) {
        if (tin[i] == -1)
            dfsBridge(i, -1, adj);
    }

    return bridges;
}


// ==================== ARTICULATION POINTS ====================
// Usage: build adj, then call articulationPoints(n, adj).

vector<int> tinArt, lowArt;
vector<bool> isArt;
int timerArt;

void dfsArt(int u, int p, vector<vector<int>>& adj) {
    tinArt[u] = lowArt[u] = timerArt++;

    int children = 0;

    for (int v : adj[u]) {
        if (v == p)
            continue;

        if (tinArt[v] != -1) {
            lowArt[u] = min(lowArt[u], tinArt[v]);
        }
        else {
            dfsArt(v, u, adj);

            lowArt[u] = min(lowArt[u], lowArt[v]);

            if (p != -1 && lowArt[v] >= tinArt[u])
                isArt[u] = true;

            children++;
        }
    }

    if (p == -1 && children > 1)
        isArt[u] = true;
}

vector<int> articulationPoints(
    int n, vector<vector<int>>& adj) {

    tinArt.assign(n + 1, -1);
    lowArt.assign(n + 1, -1);
    isArt.assign(n + 1, false);
    timerArt = 0;

    for (int i = 1; i <= n; i++) {
        if (tinArt[i] == -1)
            dfsArt(i, -1, adj);
    }

    vector<int> ans;

    for (int i = 1; i <= n; i++) {
        if (isArt[i])
            ans.push_back(i);
    }

    return ans;
}
