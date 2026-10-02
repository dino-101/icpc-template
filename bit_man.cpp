



// ==================== BIT MANIPULATION ====================

__builtin_popcount(x);            // number of set bits in int
__builtin_popcountll(x);          // number of set bits in long long
__builtin_ctz(x);                 // number of trailing 0s
__builtin_ctzll(x);               // number of trailing 0s in long long
__builtin_clz(x);                 // number of leading 0s (32-bit)
__builtin_clzll(x);               // number of leading 0s (64-bit)
__builtin_parity(x);              // 1 if odd number of set bits, else 0
__builtin_parityll(x);            // same for long long
__builtin_ffs(x);                 // 1-indexed position of first set bit, 0 if x=0
__builtin_ffsll(x);               // same for long long

x & y;                            // bitwise AND
x | y;                            // bitwise OR
x ^ y;                            // bitwise XOR
~x;                               // bitwise NOT
x << k;                           // left shift by k
x >> k;                           // right shift by k

(x >> i) & 1;                    // check i-th bit
x & (1LL << i);                  // check if i-th bit is set
x |= (1LL << i);                 // set i-th bit
x &= ~(1LL << i);                // clear i-th bit
x ^= (1LL << i);                 // toggle i-th bit

x & -x;                           // isolate lowest set bit
x & (x - 1);                     // remove lowest set bit
x > 0 && !(x & (x - 1));         // check if x is power of 2
31 - __builtin_clz(x);            // floor(log2(x))
63 - __builtin_clzll(x);          // floor(log2(x)) for long long
1LL << (63 - __builtin_clzll(x)); // highest set bit value

for(int sub=mask;sub;sub=(sub-1)&mask) {} // iterate all non-empty submasks
for(int sub=mask;;sub=(sub-1)&mask){       // iterate all submasks including 0
    // ...
    if(sub==0) break;
}

for(int mask=0;mask<(1<<n);mask++) {}      // iterate all subsets

bitset<64> bs;
bs[i];                            // get i-th bit
bs.set();                         // set all bits
bs.set(i);                        // set i-th bit
bs.reset();                       // clear all bits
bs.reset(i);                      // clear i-th bit
bs.flip();                        // toggle all bits
bs.flip(i);                       // toggle i-th bit
bs.count();                       // number of set bits
bs.any();                         // at least one bit set?
bs.none();                        // no bits set?
bs.all();                         // all bits set?
bs.to_ulong();                    // convert to unsigned long
bs.to_ullong();                   // convert to unsigned long long
bs.to_string();                   // convert to string

// C++20 <bit>
popcount(x);                      // number of set bits
has_single_bit(x);                // power of 2?
countl_zero(x);                   // leading 0s
countr_zero(x);                   // trailing 0s
bit_width(x);                     // floor(log2(x))+1
bit_floor(x);                     // greatest power of 2 <= x
bit_ceil(x);                      // smallest power of 2 >= x
rotl(x,k);                        // rotate bits left
rotr(x,k);                        // rotate bits right

// Note: clz/ctz and their ll versions are undefined for x=0.

// some tricks

// parity of set bits in a ^ b
// let x be the no. of set bits in a, 
// and y = no. of set bits in b.
// so parity of set bits in a ^ b = parity(x + y)

// a + b = (a ^ b) + 2 * (a & b)
// a + b = (a | b) + (a & b)

// if we divide a number with 2 ^ k, then we get the last k bits in binary as the remainder
// similarly if we divide a number in base 3 by 3 ^ k, then last k bits is the remainder 



// if we take xor or add a number(n) with some odd number, then the parity of number(n) changes.
// similarly if we take xor or add a number(n) with some even number, then the parity of number(n) does not changes.


// Both numbers have the same parity (both even or both odd)
// Their XOR result will always be even.

// Numbers have different parity (one even, one odd)
// Their XOR result will always be odd.

// i.e. if x and y are of different parity then x ^ y is odd