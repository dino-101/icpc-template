

// 4 directions
int dr4[4] = {-1, 1, 0, 0};
int dc4[4] = {0, 0, -1, 1};

// 8 directions
int dr8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Knight moves
int drKnight[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dcKnight[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

// primes after 1e9 + 7
// 10 primes after 1e9 + 7
const int primes[] = {
    1000000009,
    1000000021,
    1000000033,
    1000000087,
    1000000093,
    1000000097,
    1000000103,
    1000000123,
    1000000181,
    1000000207
};


// dice stuff
vector<vector<pair<int, int>>> arr(13);
  arr[0] = {{}};
  arr[1] = {{}};
  arr[2] = {{1, 1}};
  arr[3] = {{1, 2}, {2, 1}};
  arr[4] = {{1, 3}, {3, 1}, {2, 2}};
  arr[5] = {{1, 4}, {4, 1}, {2, 3}, {3, 2}};
  arr[6] = {{1, 5}, {5, 1}, {2, 4}, {4, 2}, {3, 3}};
  arr[7] = {{1, 6}, {6, 1}, {2, 5}, {5, 2}, {3, 4}, {4, 3}};
  arr[8] = {{2, 6}, {6, 2}, {3, 5}, {5, 3}, {4, 4}};
  arr[9] = {{4, 5}, {5, 4}, {3, 6}, {6, 3}};
  arr[10] = {{5, 5}, {4, 6}, {6, 4}};
  arr[11] = {{5, 6}, {6, 5}};
  arr[12] = {{6, 6}};


// XOR from 1 to n
// n % 4 == 0 -> n
// n % 4 == 1 -> 1
// n % 4 == 2 -> n+1
// n % 4 == 3 -> 0

// AND from 1 to n
// 1 & 2 & ... & n
// Keep clearing the highest set bit of n:
// ans = n;
// while(ans & (ans-1)) ans &= ans-1;

// OR from 1 to n
// 1 | 2 | ... | n
// If n = 0 -> 0
// Otherwise: (1LL << (floor(log2(n))+1)) - 1

// XOR of l to r
// xor(l..r) = xor(1..r) ^ xor(1..l-1)

// Sum of first n integers
// 1 + 2 + ... + n = n*(n+1)/2

// Sum of squares
// 1² + 2² + ... + n² = n*(n+1)*(2*n+1)/6

// Sum of cubes
// 1³ + 2³ + ... + n³ = (n*(n+1)/2)²

// Number of set bits in all numbers from 1 to n
// Can be calculated bit-by-bit using cycles of:
// 0000...0, 0000...1, ..., 1111...1

// Highest power of 2 <= n
// 1LL << floor(log2(n))
// = 1LL << (63-__builtin_clzll(n))

// Smallest power of 2 >= n
// 1LL << ceil(log2(n))
// = bit_ceil((unsigned long long)n)

// Number of multiples of k in [1,n]
// n/k

// Number of integers in [1,n] divisible by a or b
// n/a + n/b - n/lcm(a,b)

// Number of integers in [1,n] coprime with n
// phi(n)

// Number of divisors of n
// If n = p1^a1 * p2^a2 * ... * pk^ak
// divisors = (a1+1)*(a2+1)*...*(ak+1)

// Sum of divisors of n
// If n = p1^a1 * ... * pk^ak
// sumDiv = Π (p_i^(a_i+1)-1)/(p_i-1)

// Trailing zeroes in n!
// floor(n/5) + floor(n/25) + floor(n/125) + ...

// Number of digits of n in base b
// floor(log_b(n)) + 1

// Sum of digits of n in base 10
// n%10 + (n/10)%10 + ...

// Gray code of n
// g = n ^ (n >> 1)

// Recover n from Gray code g
// n = g ^ (g>>1) ^ (g>>2) ^ ... 

// Check power of 2
// n > 0 && (n & (n-1)) == 0

// Check power of 4
// n > 0 && (n & (n-1)) == 0 && (n & 0x55555555)

// Number of set bits in x
// __builtin_popcount(x)

// Lowest set bit
// x & -x

// Remove lowest set bit
// x & (x-1)

// Highest set bit position
// floor(log2(x))

// XOR property
// x ^ x = 0
// x ^ 0 = x
// x ^ y ^ x = y

// If a1 ^ a2 ^ ... ^ an = 0,
// then XOR of all elements is zero.

// XOR of all elements occurring twice + one occurring once
// gives the unique element.

// XOR of 1..(2^k - 1)
// = 0 if k is even
// = 2^k - 1 if k is odd


// ==================== COMMON IDENTITIES ====================

// (a+b)^2 = a²+2ab+b²

// (a-b)^2 = a²-2ab+b²

// a²-b² = (a-b)(a+b)

// a³-b³ = (a-b)(a²+ab+b²)

// a³+b³ = (a+b)(a²-ab+b²)

// a^n-b^n is divisible by a-b

// a^n+b^n is divisible by a+b when n is odd
