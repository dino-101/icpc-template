

struct Combi {
    // ankitt combi template
    vector<int> fact, ifact;
    const int MOD = 1e9 + 7;

    int mult(int x, int y) {
        return (x * 1LL * y) % MOD;
    }

    int modpow(int x, int y) {
        int res = 1;
        while (y) {
            if (y & 1) res = mult(res, x);
            x = mult(x, x);
            y >>= 1;
        }
        return res;
    }

    int nCr(int n, int r) {
        if (n < r) return 0;
        return mult(fact[n], mult(ifact[r], ifact[n - r]));
    }

    void init(int N) {
        fact.resize(N + 1);
        ifact.resize(N + 1);
        fact[0] = ifact[0] = 1;
        for (int i = 1; i <= N; i++)
            fact[i] = mult(fact[i - 1], i);
        ifact[N] = modpow(fact[N], MOD - 2);
        for (int i = N - 1; i >= 1; i--)
            ifact[i] = mult(ifact[i + 1], i + 1);
    }
};

int main() {
    int n, r;
    cin >> n >> r;

    Combi C;
    C.init(n);  // precompute up to n

    cout << C.nCr(n, r) << endl;

    return 0;
}