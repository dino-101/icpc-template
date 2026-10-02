

// ==================== STRING HASHING ====================
// Usage: Hashing H(s); get double hash of substring [l,r] with H.substringHash(l,r).

struct Hashing{
    string s;
    int n;
    int primes;
    vector<ll> hashPrimes = {1000000009, 100000007};
    const ll base = 31;
    vector<vector<ll>> hashValues;
    vector<vector<ll>> powersOfBase;
    vector<vector<ll>> inversePowersOfBase;
    Hashing(string a){
        primes = sz(hashPrimes);
        hashValues.resize(primes);
        powersOfBase.resize(primes);
        inversePowersOfBase.resize(primes);
        s = a;
        n = s.length(); 
        for(int i = 0; i < sz(hashPrimes); i++) {
            powersOfBase[i].resize(n + 1);
            inversePowersOfBase[i].resize(n + 1);
            powersOfBase[i][0] = 1;
            for(int j = 1; j <= n; j++){
                powersOfBase[i][j] = (base * powersOfBase[i][j - 1]) % hashPrimes[i];
            }
            inversePowersOfBase[i][n] = mminvprime(powersOfBase[i][n], hashPrimes[i]);
            for(int j = n - 1; j >= 0; j--){
                inversePowersOfBase[i][j] = mod_mul(inversePowersOfBase[i][j + 1], base, hashPrimes[i]);
            } 
        }
        for(int i = 0; i < sz(hashPrimes); i++) {
            hashValues[i].resize(n);
            for(int j = 0; j < n; j++){
                hashValues[i][j] = ((s[j] - 'a' + 1LL) * powersOfBase[i][j]) % hashPrimes[i];
                hashValues[i][j] = (hashValues[i][j] + (j > 0 ? hashValues[i][j - 1] : 0LL)) % hashPrimes[i];
            }
        }
    }
    vector<ll> substringHash(int l, int r){
        vector<ll> hash(primes);
        for(int i = 0; i < primes; i++){
            ll val1 = hashValues[i][r];
            ll val2 = l > 0 ? hashValues[i][l - 1] : 0LL;
            hash[i] = mod_mul(mod_sub(val1, val2, hashPrimes[i]), inversePowersOfBase[i][l], hashPrimes[i]);
        }
        return hash;
    }
};



// ==================== MANACHER'S ALGORITHM ====================
// Usage: Manacher M(s); M.pal[l][r] can be checked in O(1);
// longest odd/even palindrome lengths are available through d1/d2.
//
// d1[i] = radius of odd palindrome centered at i
// d2[i] = radius of even palindrome centered between i-1 and i

struct Manacher
{
    int n;
    string s;
    vector<int> d1, d2;

    Manacher(string _s)
    {
        s = _s;
        n = s.size();

        d1.assign(n, 0);
        d2.assign(n, 0);

        // Odd length palindromes
        for (int i = 0, l = 0, r = -1; i < n; i++)
        {
            int k = (i > r ? 1 : min(d1[l + r - i], r - i + 1));

            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k])
                k++;

            d1[i] = k--;

            if (i + k > r)
            {
                l = i - k;
                r = i + k;
            }
        }

        // Even length palindromes
        for (int i = 0, l = 0, r = -1; i < n; i++)
        {
            int k = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1));

            while (i - k - 1 >= 0 && i + k < n &&
                   s[i - k - 1] == s[i + k])
                k++;

            d2[i] = k--;

            if (i + k > r)
            {
                l = i - k - 1;
                r = i + k;
            }
        }
    }

    // Check if s[l..r] is a palindrome in O(1)
    bool isPalindrome(int l, int r)
    {
        int len = r - l + 1;

        if (len & 1)
        {
            int mid = (l + r) / 2;
            return d1[mid] >= len / 2 + 1;
        }
        else
        {
            int mid = (l + r + 1) / 2;
            return d2[mid] >= len / 2;
        }
    }

    // Longest palindromic substring length
    int longestPalindrome()
    {
        int ans = 0;

        for (int x : d1)
            ans = max(ans, 2 * x - 1);

        for (int x : d2)
            ans = max(ans, 2 * x);

        return ans;
    }
};



// ==================== AHO-CORASICK ====================
// Usage:
// AhoCorasick AC;
// AC.insert("he"); AC.insert("she"); AC.insert("his"); AC.insert("hers");
// AC.build();
// auto ans = AC.search("ahishers");
// ans[i] = occurrences of the i-th inserted pattern.
// Example: ans = {1,1,1,1} for the above patterns/text.
// Assumes lowercase English letters 'a' to 'z'.

struct AhoCorasick
{
    struct Node
    {
        int nxt[26];
        int link;

        Node()
        {
            fill(nxt, nxt + 26, -1);
            link = 0;
        }
    };

    vector<Node> trie;
    vector<int> patternNode;

    AhoCorasick()
    {
        trie.push_back(Node());
    }

    int insert(string s)
    {
        int u = 0;

        for (char c : s)
        {
            int x = c - 'a';

            if (trie[u].nxt[x] == -1)
            {
                trie[u].nxt[x] = trie.size();
                trie.push_back(Node());
            }

            u = trie[u].nxt[x];
        }

        patternNode.push_back(u);
        return patternNode.size() - 1;
    }

    void build()
    {
        queue<int> q;

        for (int c = 0; c < 26; c++)
        {
            int v = trie[0].nxt[c];

            if (v != -1)
                q.push(v);
            else
                trie[0].nxt[c] = 0;
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int c = 0; c < 26; c++)
            {
                int v = trie[u].nxt[c];

                if (v != -1)
                {
                    trie[v].link = trie[trie[u].link].nxt[c];
                    q.push(v);
                }
                else
                {
                    trie[u].nxt[c] = trie[trie[u].link].nxt[c];
                }
            }
        }
    }

    vector<int> search(string text)
    {
        vector<int> ans(patternNode.size());
        vector<int> cnt(trie.size(), 0);

        int u = 0;

        for (char c : text)
        {
            u = trie[u].nxt[c - 'a'];
            cnt[u]++;
        }

        vector<vector<int>> level(trie.size());

        for (int i = 1; i < (int)trie.size(); i++)
            level[trie[i].link].push_back(i);

        vector<int> order;
        queue<int> q;
        q.push(0);

        while (!q.empty())
        {
            int x = q.front();
            q.pop();

            order.push_back(x);

            for (int v : level[x])
                q.push(v);
        }

        for (int i = (int)order.size() - 1; i > 0; i--)
        {
            int v = order[i];
            cnt[trie[v].link] += cnt[v];
        }

        for (int i = 0; i < (int)patternNode.size(); i++)
            ans[i] = cnt[patternNode[i]];

        return ans;
    }
};

