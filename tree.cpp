

// ==================== TREE DP ====================
// Example: subtree sum.
// Usage: set val[u], then call dfsTreeDP(root, 0, adj).

vector<long long> dp;

void dfsTreeDP(int u, int p, vector<vector<int>>& adj,
               vector<int>& val) {

    dp[u] = val[u];

    for (int v : adj[u]) {
        if (v == p)
            continue;

        dfsTreeDP(v, u, adj, val);

        dp[u] += dp[v];
    }
}


// ==================== REROOTING DP ====================
// Example: sum of distances from every node to all other nodes.
// dp[u] = answer for u.
// sub[u] = subtree size.
//
// Usage: build tree, then call rerooting(n, adj).

vector<int> sub;
vector<long long> dpReroot;

void dfs1(int u, int p, vector<vector<int>>& adj) {
    sub[u] = 1;

    for (int v : adj[u]) {
        if (v == p)
            continue;

        dfs1(v, u, adj);

        sub[u] += sub[v];
        dpReroot[u] += dpReroot[v] + sub[v];
    }
}

void dfs2(int u, int p, int n, vector<vector<int>>& adj) {
    for (int v : adj[u]) {
        if (v == p)
            continue;

        // Move root from u to v
        dpReroot[v] = dpReroot[u] - sub[v] + (n - sub[v]);

        dfs2(v, u, n, adj);
    }
}

vector<long long> rerooting(int n, vector<vector<int>>& adj) {
    sub.assign(n + 1, 0);
    dpReroot.assign(n + 1, 0);

    dfs1(1, 0, adj);
    dfs2(1, 0, n, adj);

    return dpReroot;
}


// ==================== BINARY LIFTING ====================
// 1-indexed tree
// Supports:
//   - kth ancestor
//   - LCA
//   - distance between two nodes

// Usage: build adj from n-1 edges, then call init(n, adj, root); 
// use lca(u,v), kthAncestor(u,k), and dist(u,v).

const int LOG = 20; // use 20 for n <= 1e6, or 30/32 for larger n

vector<vector<int>> up;
vector<int> depth;

void dfs(int u, int p, vector<vector<int>>& adj) {
    up[u][0] = p;

    for (int j = 1; j < LOG; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }

    for (int v : adj[u]) {
        if (v == p)
            continue;

        depth[v] = depth[u] + 1;
        dfs(v, u, adj);
    }
}

void init(int n, vector<vector<int>>& adj, int root = 1) {
    up.assign(n + 1, vector<int>(LOG));
    depth.assign(n + 1, 0);

    dfs(root, root, adj);
}


// ---------- K-th Ancestor ----------

int kthAncestor(int u, int k) {
    for (int j = 0; j < LOG; j++) {
        if (k & (1 << j)) {
            u = up[u][j];
        }
    }

    return u;
}


// ---------- LCA ----------

int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    // Bring u to same depth as v
    int diff = depth[u] - depth[v];

    for (int j = 0; j < LOG; j++) {
        if (diff & (1 << j)) {
            u = up[u][j];
        }
    }

    if (u == v)
        return u;

    // Lift both nodes
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}


// ---------- Distance ----------

int dist(int u, int v) {
    int L = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[L];
}


// ==================== EULER TOUR ====================
// Usage: build graph from n-1 edges, then call eulerTour(1, n, val).
// tin[u] and tout[u] are positions; euler contains val[u] at both positions.

vector<vector<int>> graph;
vector<int> tin, tout, euler;
int timer = 0;

void dfs(int u, int par, vector<int>& val) {
    tin[u] = timer;
    euler[timer++] = val[u];

    for (int v : graph[u]) {
        if (v == par)
            continue;

        dfs(v, u, val);
    }

    tout[u] = timer;
    euler[timer++] = val[u];
}

void eulerTour(int root, int n, vector<int>& val) {
    tin.resize(n + 1);
    tout.resize(n + 1);
    euler.resize(2 * n);

    timer = 0;

    dfs(root, -1, val);
}

// ==================== TREE DIAMETER ====================
// Usage: build graph from n-1 edges, then call diameter(n, graph).

int diameter(int n, vector<vector<int>>& graph) {
    vector<int> d(n + 1, 0);

    auto dfs = [&](auto&& self, int node, int par) -> void {
        if (par != -1)
            d[node] = d[par] + 1;
        else
            d[node] = 0;

        for (int v : graph[node]) {
            if (v != par)
                self(self, v, node);
        }
    };

    dfs(dfs, 1, -1);

    int nodeval = max_element(d.begin() + 1, d.end()) - d.begin();

    d.assign(n + 1, 0);

    dfs(dfs, nodeval, -1);

    return *max_element(d.begin() + 1, d.end());
}