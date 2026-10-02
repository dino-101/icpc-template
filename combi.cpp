

// ==================== COMBINATORICS ====================
// Topics
// 1. Factorial + Inverse Factorial
// 2. nCr / nPr
// 3. Modular Inverse
// 4. Fast Power
// 5. Catalan Numbers
// 6. Stars and Bars
// 7. Derangements
// 8. Inclusion-Exclusion
// 9. Pascal's Triangle
// 10. Lucas Theorem
// 11. Multinomial Coefficient


// Usage: Combi C; C.init(N); use C.nCr(n,r), C.nPr(n,r), C.catalan(n), etc.
// Note: For catalan(n), init(2*n) is required.
// Note: For multinomial, init(sum(a)) is required.

struct Combi {
    vector<int> fact, ifact;
    const int MOD = 1e9 + 7;

    int mult(int x, int y) {
        return x * 1LL * y % MOD;
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

    int modinv(int x) {
        return modpow(x, MOD - 2);
    }

    void init(int N) {
        fact.resize(N + 1);
        ifact.resize(N + 1);

        fact[0] = ifact[0] = 1;

        for (int i = 1; i <= N; i++)
            fact[i] = mult(fact[i - 1], i);

        ifact[N] = modinv(fact[N]);

        for (int i = N - 1; i >= 1; i--)
            ifact[i] = mult(ifact[i + 1], i + 1);
    }

    int nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        return mult(fact[n], mult(ifact[r], ifact[n - r]));
    }

    int nPr(int n, int r) {
        if (r < 0 || r > n) return 0;
        return mult(fact[n], ifact[n - r]);
    }

    // Catalan(n) = C(2n,n)/(n+1)
    int catalan(int n) {
        return mult(nCr(2 * n, n), modinv(n + 1));
    }

    // Multinomial: n! / (a1! * a2! * ...)
    int multinomial(vector<int>& a) {
        int n = 0;
        for (int x : a) n += x;

        int ans = fact[n];
        for (int x : a)
            ans = mult(ans, ifact[x]);

        return ans;
    }

    // Derangement: !n
    vector<int> derangement(int n) {
        vector<int> d(n + 1);
        d[0] = 1;
        if (n >= 1) d[1] = 0;

        for (int i = 2; i <= n; i++)
            d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % MOD;

        return d;
    }

    // Stars and Bars:
    // x1+x2+...+xk=n, xi>=0 -> C(n+k-1,k-1)
    // x1+x2+...+xk=n, xi>=1 -> C(n-1,k-1)

    // Lucas:
    // C(n,r) mod p = C(n/p,r/p) * C(n%p,r%p) mod p
    // Use when MOD=p is prime and n can be >= p.

    // Pascal:
    // C(n,r) = C(n-1,r-1) + C(n-1,r)
};

// int main() {
//     int n, r;
//     cin >> n >> r;
//
//     Combi C;
//     C.init(n);
//
//     cout << C.nCr(n, r) << endl;
// }


// Think Catalan when you are counting structures that are nested, balanced, or non-crossing, especially when choosing a left part + right part recursively.
// Typical signs:
// - Balanced / properly nested structures → parentheses (number of valid arrangements of n pairs of parentheses)
// - number of ways 2n people can pair up without crossing handshakes.
// - Non-crossing structures → polygon triangulation, chords
// - Recursive binary splitting → BSTs, full binary trees
// - You see a recurrence like
//   dp[n] = Σ dp[i] * dp[n-1-i]