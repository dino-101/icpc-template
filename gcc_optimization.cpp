#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("O3") 

// use at own risk
#pragma GCC optimize("no-stack-protector")


// fast io
std::ios::sync_with_stdio(false); 
std::cin.tie(nullptr);

// ultra fast io from file
// source: https://github.com/kth-competitive-programming/kactl/blob/main/content/various/FastInput.h
#pragma once

inline char gc() { // like getchar()
	static char buf[1 << 16];
	static size_t bc, be;
	if (bc >= be) {
		buf[0] = 0, bc = 0;
		be = fread(buf, 1, sizeof(buf), stdin);
	}
	return buf[bc++]; // returns 0 on EOF
}

int readInt() {
	int a, c;
	while ((a = gc()) < 40);
	if (a == '-') return -readInt();
	while ((c = gc()) >= 48) a = a * 10 + c - 480;
	return a - 48;
}


// assembly inline
 __attribute__((always_inline)) int func(...) const noexcept __attribute__((hot));


// fast Mod
// source: https://github.com/kth-competitive-programming/kactl/blob/main/content/various/FastMod.h
#pragma once

typedef unsigned long long ull;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) { // a % b + (0 or b)
		return a - (ull)((__uint128_t(m) * a) >> 64) * b;
	}
};
