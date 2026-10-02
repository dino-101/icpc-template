// ==================== NUMBER THEORY ====================
// Topics
// 1. GCD / LCM
// 2. Extended GCD
// 3. Modular Inverse / Fast Power
// 4. Trial Division
// 5. Sieve of Eratosthenes
// 6. Smallest Prime Factor (SPF)
// 7. Prime Factorization using SPF
// 8. Divisors
// 9. Euler Totient
// 10. Totient Sieve
// 11. Mobius Sieve
// 12. Linear Diophantine Equation
// 13. Chinese Remainder Theorem
// 14. Segmented Sieve
// 15. Miller-Rabin Primality Test

// ==================== GCD / LCM ====================
// Usage: gcdll(a,b), lcmll(a,b)

int gcdll(int a, int b)
{
    return b ? gcdll(b, a % b) : abs(a);
}

int lcmll(int a, int b)
{
    return a / gcdll(a, b) * b;
}

// ==================== FAST POWER ====================
// Usage: modpow(a,b,mod)

int modpow(int a, int b, int mod)
{
    int res = 1;

    while (b)
    {
        if (b & 1)
            res = (__int128)res * a % mod;

        a = (__int128)a * a % mod;
        b >>= 1;
    }

    return res;
}

// ==================== EXTENDED GCD ====================
// ax + by = gcd(a,b)
// Usage: auto [g,x,y] = extgcd(a,b);

tuple<int,int,int> extgcd(int a, int b)
{
    if (b == 0)
        return {abs(a), a >= 0 ? 1 : -1, 0};

    auto [g, x1, y1] = extgcd(b, a % b);

    int x = y1;
    int y = x1 - (a / b) * y1;

    return {g, x, y};
}

// ==================== MODULAR INVERSE ====================
// Usage: modinv(a,m), returns -1 if inverse doesn't exist.

int modinv(int a, int m)
{
    auto [g, x, y] = extgcd(a, m);

    if (g != 1)
        return -1;

    return (x % m + m) % m;
}

// ==================== TRIAL DIVISION ====================
// Usage: auto pf = primeFactors(n);
// Returns prime factors with repetition.
// Distinct prime factors: use set<int>(pf.begin(),pf.end()).

vector<int> primeFactors(int n)
{
    vector<int> pf;

    for (int i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            pf.push_back(i);
            n /= i;
        }
    }

    if (n > 1)
        pf.push_back(n);

    return pf;
}

// ==================== SIEVE OF ERATOSTHENES ====================
// Usage: auto isPrime = sieve(N); primes are i where isPrime[i]=true.

vector<bool> sieve(int n)
{
    vector<bool> isPrime(n + 1, true);

    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;

    for (int i = 2; i * i <= n; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }

    return isPrime;
}

// ==================== SMALLEST PRIME FACTOR ====================
// Usage: auto spf = buildSPF(N); then spf[x] gives smallest prime factor.

vector<int> buildSPF(int n)
{
    vector<int> spf(n + 1);

    iota(spf.begin(), spf.end(), 0);

    if (n >= 1)
        spf[1] = 1;

    for (int i = 2; i * i <= n; i++)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j <= n; j += i)
            {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }

    return spf;
}

// ==================== FACTORIZATION USING SPF ====================
// Usage: vector<int> spf=buildSPF(N); auto pf=factorize(n,spf);

vector<int> factorize(int n, vector<int>& spf)
{
    vector<int> pf;

    while (n != 1)
    {
        pf.push_back(spf[n]);
        n /= spf[n];
    }

    return pf;
}

// ==================== DIVISORS ====================
// Usage: auto d = divisors(n);

vector<int> divisors(int n)
{
    vector<int> d;

    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            d.push_back(i);

            if (i * i != n)
                d.push_back(n / i);
        }
    }

    return d;
}

// ==================== EULER TOTIENT ====================
// phi(n) = count of integers in [1,n] coprime with n
// Usage: int x = phi(n);

int phi(int n)
{
    int ans = n;

    for (int p = 2; p * p <= n; p++)
    {
        if (n % p == 0)
        {
            while (n % p == 0)
                n /= p;

            ans -= ans / p;
        }
    }

    if (n > 1)
        ans -= ans / n;

    return ans;
}

// ==================== TOTIENT SIEVE ====================
// Usage: auto ph = phiSieve(N); ph[i] = phi(i).

vector<int> phiSieve(int n)
{
    vector<int> ph(n + 1);

    for (int i = 0; i <= n; i++)
        ph[i] = i;

    for (int p = 2; p <= n; p++)
    {
        if (ph[p] == p)
        {
            for (int j = p; j <= n; j += p)
                ph[j] -= ph[j] / p;
        }
    }

    return ph;
}

// ==================== MOBIUS SIEVE ====================
// mu(n)=0 if n has squared prime factor
// mu(n)=(-1)^k if n has k distinct prime factors
// Usage: auto mu = mobiusSieve(N);

vector<int> mobiusSieve(int n)
{
    vector<int> mu(n + 1), primes;
    vector<bool> composite(n + 1, false);

    mu[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        if (!composite[i])
        {
            primes.push_back(i);
            mu[i] = -1;
        }

        for (int p : primes)
        {
            if (i * p > n)
                break;

            composite[i * p] = true;

            if (i % p == 0)
            {
                mu[i * p] = 0;
                break;
            }

            mu[i * p] = -mu[i];
        }
    }

    return mu;
}

// ==================== LINEAR DIOPHANTINE ====================
// Solves: ax + by = c
// Usage: int x,y; bool ok=linearDiophantine(a,b,c,x,y);

bool linearDiophantine(int a, int b, int c, int& x, int& y)
{
    auto [g, x0, y0] = extgcd(a, b);

    if (c % g != 0)
        return false;

    x = x0 * (c / g);
    y = y0 * (c / g);

    return true;
}

// ==================== CHINESE REMAINDER THEOREM ====================
// x = a1 (mod m1)
// x = a2 (mod m2)
// Works even when m1,m2 are not coprime.
// Usage: auto [x,mod]=CRT(a1,m1,a2,m2); {-1,-1} if no solution.

pair<int,int> CRT(int a1, int m1, int a2, int m2)
{
    auto [g, p, q] = extgcd(m1, m2);

    int diff = a2 - a1;

    if (diff % g != 0)
        return {-1, -1};

    int mod2 = m2 / g;

    int t = 0;

    if (mod2 != 1)
    {
        t = (diff / g) % mod2;
        t = (t * ((p % mod2 + mod2) % mod2)) % mod2;
    }

    int mod = m1 / g * m2;
    int x = (a1 + m1 * t) % mod;

    if (x < 0)
        x += mod;

    return {x, mod};
}

// ==================== SEGMENTED SIEVE ====================
// Usage: auto primes=segmentedSieve(L,R); returns primes in [L,R].

vector<int> segmentedSieve(int L, int R)
{
    int lim = sqrtl(R) + 1;

    vector<bool> isPrime(lim + 1, true);
    isPrime[0] = isPrime[1] = false;

    vector<int> primes;

    for (int i = 2; i <= lim; i++)
    {
        if (!isPrime[i])
            continue;

        primes.push_back(i);

        if (i * i <= lim)
        {
            for (int j = i * i; j <= lim; j += i)
                isPrime[j] = false;
        }
    }

    vector<bool> seg(R - L + 1, true);

    if (L == 1)
        seg[0] = false;

    for (int p : primes)
    {
        if (1LL * p * p > R)
            break;

        int start = max(1LL * p * p,
                        ((L + p - 1) / p) * 1LL * p);

        for (int j = start; j <= R; j += p)
            seg[j - L] = false;
    }

    vector<int> ans;

    for (int i = L; i <= R; i++)
    {
        if (seg[i - L])
            ans.push_back(i);
    }

    return ans;
}

// ==================== MILLER-RABIN ====================
// Usage: MillerRabin(n) -> true if n is prime.
// Deterministic for 64-bit integers.

int _mr_pow(int a, int b, int mod)
{
    int res = 1;

    while (b)
    {
        if (b & 1)
            res = (__int128)res * a % mod;

        a = (__int128)a * a % mod;
        b >>= 1;
    }

    return res;
}

bool _mr_composite(int n, int a, int d, int s)
{
    int x = _mr_pow(a, d, n);

    if (x == 1 || x == n - 1)
        return false;

    for (int r = 1; r < s; r++)
    {
        x = (__int128)x * x % n;

        if (x == n - 1)
            return false;
    }

    return true;
}

bool MillerRabin(int n)
{
    if (n < 2)
        return false;

    for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if (n % p == 0)
            return n == p;
    }

    int d = n - 1;
    int s = 0;

    while ((d & 1) == 0)
    {
        d >>= 1;
        s++;
    }

    // Deterministic for 64-bit integers
    for (int a : {2LL, 325LL, 9375LL, 28178LL,
                  450775LL, 9780504LL, 1795265022LL})
    {
        if (a % n == 0)
            continue;

        if (_mr_composite(n, a, d, s))
            return false;
    }

    return true;
}


