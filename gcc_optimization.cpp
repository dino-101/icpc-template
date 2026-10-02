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


// assembly inline
 __attribute__((always_inline)) int func(...) const noexcept __attribute__((hot))
