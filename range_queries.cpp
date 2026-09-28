

// ==================== SEGMENT TREE ====================
// Usage: build with build_tree(1, n, arr, 1); 
// point update with update(1, n, 1, pos, val); 
// query with query(1, n, 1, l, r).

vector<int> segtree;

int combine(int left, int right)
{
    return min(left, right); // change to +, max, gcd, etc.
}

void build_tree(int start, int end, vector<int>& arr, int idx)
{
    if (start == end)
    {
        segtree[idx] = arr[start];
        return;
    }

    int mid = (start + end) / 2;

    build_tree(start, mid, arr, 2 * idx);
    build_tree(mid + 1, end, arr, 2 * idx + 1);

    segtree[idx] = combine(segtree[2 * idx], segtree[2 * idx + 1]);
}

void update(int start, int end, int idx, int pos, int val)
{
    if (start == end)
    {
        segtree[idx] = val;
        return;
    }

    int mid = (start + end) / 2;

    if (pos <= mid)
        update(start, mid, 2 * idx, pos, val);
    else
        update(mid + 1, end, 2 * idx + 1, pos, val);

    segtree[idx] = combine(segtree[2 * idx], segtree[2 * idx + 1]);
}

int query(int start, int end, int idx, int l, int r)
{
    if (l <= start && end <= r)
        return segtree[idx];

    if (r < start || end < l)
        return LLONG_MAX; // identity for min

    int mid = (start + end) / 2;

    int leftAns = query(start, mid, 2 * idx, l, r);
    int rightAns = query(mid + 1, end, 2 * idx + 1, l, r);

    return combine(leftAns, rightAns);
}


// ==================== LAZY SEGMENT TREE ====================
// Usage: build with build(arr); 
// range add with update_add(l,r,x); 
// range set with update_set(l,r,x); 
// query with query(l,r).

struct segmenttree
{
    int n;
    vector<int> st;
    vector<int> lazy_add;
    vector<int> lazy_set;
    vector<bool> has_lazy_set;

    void init(int _n)
    {
        n = _n;

        st.assign(4 * n + 5, 0);
        lazy_add.assign(4 * n + 5, 0);
        lazy_set.assign(4 * n + 5, 0);
        has_lazy_set.assign(4 * n + 5, false);
    }

    int combine(int a, int b)
    {
        return a + b; // sum segment tree
    }

    void push(int start, int end, int node)
    {
        // Pending range set
        if (has_lazy_set[node])
        {
            st[node] = (end - start + 1) * lazy_set[node];

            if (start != end)
            {
                has_lazy_set[2 * node] = true;
                has_lazy_set[2 * node + 1] = true;

                lazy_set[2 * node] = lazy_set[node];
                lazy_set[2 * node + 1] = lazy_set[node];

                lazy_add[2 * node] = 0;
                lazy_add[2 * node + 1] = 0;
            }

            has_lazy_set[node] = false;
        }

        // Pending range addition
        if (lazy_add[node] != 0)
        {
            st[node] += (end - start + 1) * lazy_add[node];

            if (start != end)
            {
                if (has_lazy_set[2 * node])
                    lazy_set[2 * node] += lazy_add[node];
                else
                    lazy_add[2 * node] += lazy_add[node];

                if (has_lazy_set[2 * node + 1])
                    lazy_set[2 * node + 1] += lazy_add[node];
                else
                    lazy_add[2 * node + 1] += lazy_add[node];
            }

            lazy_add[node] = 0;
        }
    }

    void build(int start, int end, int node, vector<int>& arr)
    {
        if (start == end)
        {
            st[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;

        build(start, mid, 2 * node, arr);
        build(mid + 1, end, 2 * node + 1, arr);

        st[node] = combine(st[2 * node], st[2 * node + 1]);
    }

    void build(vector<int>& arr)
    {
        build(1, n, 1, arr);
    }

    // Range Add
    void range_add(int start, int end, int node,
                   int l, int r, int val)
    {
        push(start, end, node);

        if (start > r || end < l)
            return;

        if (l <= start && end <= r)
        {
            lazy_add[node] += val;
            push(start, end, node);
            return;
        }

        int mid = (start + end) / 2;

        range_add(start, mid, 2 * node, l, r, val);
        range_add(mid + 1, end, 2 * node + 1, l, r, val);

        st[node] = combine(st[2 * node], st[2 * node + 1]);
    }

    void update_add(int l, int r, int val)
    {
        range_add(1, n, 1, l, r, val);
    }

    // Range Set
    void range_set(int start, int end, int node,
                   int l, int r, int val)
    {
        push(start, end, node);

        if (start > r || end < l)
            return;

        if (l <= start && end <= r)
        {
            has_lazy_set[node] = true;
            lazy_set[node] = val;
            lazy_add[node] = 0;

            push(start, end, node);
            return;
        }

        int mid = (start + end) / 2;

        range_set(start, mid, 2 * node, l, r, val);
        range_set(mid + 1, end, 2 * node + 1, l, r, val);

        st[node] = combine(st[2 * node], st[2 * node + 1]);
    }

    void update_set(int l, int r, int val)
    {
        range_set(1, n, 1, l, r, val);
    }

    // Range Query
    int query(int start, int end, int node,
              int l, int r)
    {
        push(start, end, node);

        if (start > r || end < l)
            return 0; // identity for sum

        if (l <= start && end <= r)
            return st[node];

        int mid = (start + end) / 2;

        return combine(
            query(start, mid, 2 * node, l, r),
            query(mid + 1, end, 2 * node + 1, l, r)
        );
    }

    int query(int l, int r)
    {
        return query(1, n, 1, l, r);
    }
};


// ==================== FENWICK TREE / BIT ====================
// Usage: create BIT(n); add(pos,val) for point update; sum(l,r) for range query.

struct BIT
{
    int n;
    vector<int> bit;

    BIT(int _n)
    {
        n = _n;
        bit.assign(n + 1, 0);
    }

    void add(int idx, int val)
    {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    int sum(int idx)
    {
        int ans = 0;

        for (; idx > 0; idx -= idx & -idx)
            ans += bit[idx];

        return ans;
    }

    int sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
};



// ==================== SPARSE TABLE ====================
// Usage: build with build(arr); query static range [l,r] with query(l,r).

struct SparseTable
{
    int n, LOG;
    vector<vector<int>> st;
    vector<int> lg;

    int combine(int a, int b)
    {
        return min(a, b); // change to max, gcd, etc.
    }

    void build(vector<int>& arr)
    {
        n = arr.size() - 1; // 1-indexed
        LOG = 1;

        while ((1 << LOG) <= n)
            LOG++;

        st.assign(LOG, vector<int>(n + 1));
        lg.assign(n + 1, 0);

        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        for (int i = 1; i <= n; i++)
            st[0][i] = arr[i];

        for (int j = 1; j < LOG; j++)
        {
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                st[j][i] = combine(
                    st[j - 1][i],
                    st[j - 1][i + (1 << (j - 1))]
                );
            }
        }
    }

    int query(int l, int r)
    {
        int j = lg[r - l + 1];

        return combine(
            st[j][l],
            st[j][r - (1 << j) + 1]
        );
    }
};