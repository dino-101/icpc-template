

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


// ==================== 2D PREFIX SUM ====================
// Usage: Prefix2D P(a); query rectangle [x1,y1] to [x2,y2] with P.query(x1,y1,x2,y2).

struct Prefix2D
{
    int n, m;
    vector<vector<int>> pref;

    Prefix2D(vector<vector<int>>& a)
    {
        n = a.size() - 1;
        m = a[0].size() - 1;

        pref.assign(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                pref[i][j] = a[i][j]
                           + pref[i - 1][j]
                           + pref[i][j - 1]
                           - pref[i - 1][j - 1];
            }
        }
    }

    int query(int x1, int y1, int x2, int y2)
    {
        return pref[x2][y2]
             - pref[x1 - 1][y2]
             - pref[x2][y1 - 1]
             + pref[x1 - 1][y1 - 1];
    }
};


// ==================== 2D FENWICK TREE ====================
// Usage: BIT2D bit(n,m); bit.add(x,y,val); bit.query(x1,y1,x2,y2).

struct BIT2D
{
    int n, m;
    vector<vector<int>> bit;

    BIT2D(int _n, int _m)
    {
        n = _n;
        m = _m;
        bit.assign(n + 1, vector<int>(m + 1, 0));
    }

    void add(int x, int y, int val)
    {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j)
                bit[i][j] += val;
    }

    int sum(int x, int y)
    {
        int ans = 0;

        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                ans += bit[i][j];

        return ans;
    }

    int query(int x1, int y1, int x2, int y2)
    {
        return sum(x2, y2)
             - sum(x1 - 1, y2)
             - sum(x2, y1 - 1)
             + sum(x1 - 1, y1 - 1);
    }
};



// ==================== 2D SEGMENT TREE ====================
// Usage: SegTree2D st(a); point update with st.update(x,y,val);
// query rectangle [x1,y1] to [x2,y2] with st.query(x1,y1,x2,y2).

struct SegTree2D
{
    int n, m;
    vector<vector<int>> st;

    SegTree2D(vector<vector<int>>& a)
    {
        n = a.size() - 1;
        m = a[0].size() - 1;

        st.assign(4 * n + 5, vector<int>(4 * m + 5, 0));

        buildX(1, 1, n, a);
    }

    void buildY(int nodeX, int lx, int rx, int nodeY, int ly, int ry,
                vector<vector<int>>& a)
    {
        if (ly == ry)
        {
            if (lx == rx)
                st[nodeX][nodeY] = a[lx][ly];
            else
                st[nodeX][nodeY] = st[2 * nodeX][nodeY]
                                  + st[2 * nodeX + 1][nodeY];

            return;
        }

        int my = (ly + ry) / 2;

        buildY(nodeX, lx, rx, 2 * nodeY, ly, my, a);
        buildY(nodeX, lx, rx, 2 * nodeY + 1, my + 1, ry, a);

        st[nodeX][nodeY] = st[nodeX][2 * nodeY]
                          + st[nodeX][2 * nodeY + 1];
    }

    void buildX(int nodeX, int lx, int rx, vector<vector<int>>& a)
    {
        if (lx != rx)
        {
            int mx = (lx + rx) / 2;

            buildX(2 * nodeX, lx, mx, a);
            buildX(2 * nodeX + 1, mx + 1, rx, a);
        }

        buildY(nodeX, lx, rx, 1, 1, m, a);
    }

    void updateY(int nodeX, int lx, int rx, int nodeY, int ly, int ry,
                 int x, int y, int val)
    {
        if (ly == ry)
        {
            if (lx == rx)
                st[nodeX][nodeY] = val;
            else
                st[nodeX][nodeY] = st[2 * nodeX][nodeY]
                                  + st[2 * nodeX + 1][nodeY];

            return;
        }

        int my = (ly + ry) / 2;

        if (y <= my)
            updateY(nodeX, lx, rx, 2 * nodeY, ly, my, x, y, val);
        else
            updateY(nodeX, lx, rx, 2 * nodeY + 1, my + 1, ry, x, y, val);

        st[nodeX][nodeY] = st[nodeX][2 * nodeY]
                          + st[nodeX][2 * nodeY + 1];
    }

    void updateX(int nodeX, int lx, int rx, int x, int y, int val)
    {
        if (lx != rx)
        {
            int mx = (lx + rx) / 2;

            if (x <= mx)
                updateX(2 * nodeX, lx, mx, x, y, val);
            else
                updateX(2 * nodeX + 1, mx + 1, rx, x, y, val);
        }

        updateY(nodeX, lx, rx, 1, 1, m, x, y, val);
    }

    void update(int x, int y, int val)
    {
        updateX(1, 1, n, x, y, val);
    }

    int queryY(int nodeX, int nodeY, int ly, int ry,
               int ql, int qr)
    {
        if (qr < ly || ry < ql)
            return 0;

        if (ql <= ly && ry <= qr)
            return st[nodeX][nodeY];

        int my = (ly + ry) / 2;

        return queryY(nodeX, 2 * nodeY, ly, my, ql, qr)
             + queryY(nodeX, 2 * nodeY + 1, my + 1, ry, ql, qr);
    }

    int queryX(int nodeX, int lx, int rx,
               int qx1, int qx2, int qy1, int qy2)
    {
        if (qx2 < lx || rx < qx1)
            return 0;

        if (qx1 <= lx && rx <= qx2)
            return queryY(nodeX, 1, 1, m, qy1, qy2);

        int mx = (lx + rx) / 2;

        return queryX(2 * nodeX, lx, mx, qx1, qx2, qy1, qy2)
             + queryX(2 * nodeX + 1, mx + 1, rx,
                       qx1, qx2, qy1, qy2);
    }

    int query(int x1, int y1, int x2, int y2)
    {
        return queryX(1, 1, n, x1, x2, y1, y2);
    }
};



// ==================== SQRT DECOMPOSITION ====================
// Usage: SqrtDecomp S(arr); point update with S.update(pos,val); range query with S.query(l,r).

struct SqrtDecomp
{
    int n, block;
    vector<int> a, b;

    SqrtDecomp(vector<int>& arr)
    {
        a = arr;
        n = a.size() - 1;
        block = sqrt(n) + 1;

        b.assign(block + 1, 0);

        for (int i = 1; i <= n; i++)
            b[i / block] += a[i];
    }

    void update(int pos, int val)
    {
        b[pos / block] += val - a[pos];
        a[pos] = val;
    }

    int query(int l, int r)
    {
        int ans = 0;

        while (l <= r && l % block != 0)
            ans += a[l++];

        while (l + block - 1 <= r)
        {
            ans += b[l / block];
            l += block;
        }

        while (l <= r)
            ans += a[l++];

        return ans;
    }
};



// ==================== MO'S ALGORITHM ====================
// Usage: fill queries as {l,r,id}; sort with Mo comparator;
// maintain current range using add/remove; store answer[id].

struct Query
{
    int l, r, id;

    bool operator<(const Query& other) const
    {
        static int block = 1;
        int b1 = l / block;
        int b2 = other.l / block;

        if (b1 != b2)
            return b1 < b2;

        return (b1 & 1) ? r > other.r : r < other.r;
    }
};

// Set block size before sorting:
// Query::block is not directly settable with the above static member,
// so use this simpler comparator instead:

struct MoQuery
{
    int l, r, id;
};

int MO_BLOCK;

bool moCmp(const MoQuery& a, const MoQuery& b)
{
    int ba = a.l / MO_BLOCK;
    int bb = b.l / MO_BLOCK;

    if (ba != bb)
        return ba < bb;

    return (ba & 1) ? a.r > b.r : a.r < b.r;
}

// Example framework:
// Usage: MO_BLOCK=sqrt(n)+1; sort(q.begin(),q.end(),moCmp);
// then move [L,R] using add/remove and set ans[id].

int L = 1, R = 0;
int curAns = 0;

void add(int pos, vector<int>& a)
{
    // add a[pos] to current answer
}

void remove_(int pos, vector<int>& a)
{
    // remove a[pos] from current answer
}

// for each query:
// while(L > q.l) add(--L,a);
// while(R < q.r) add(++R,a);
// while(L < q.l) remove_(L++,a);
// while(R > q.r) remove_(R--,a);
// ans[q.id] = curAns;


