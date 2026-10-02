

// digit dp

// Q1
// Digit Sum code (atcoder - S)
// Find the number of integers between 
// 1 and K (inclusive) satisfying the following condition:
    // -- The sum of the digits in base ten is a multiple of  D.

void solve(){
  string s;
  cin >> s;
  int k;
  cin >> k;
  int n = s.size();
  vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (2, vector<int> (k + 1, -1)));
  auto dfs = [&](auto &&self, int idx, bool tight, int sum) -> int {
    if(idx == s.size()){
      if((sum % k) == 0) return 1;
      else return 0;
    }
    if(dp[idx][tight][sum] != -1) return dp[idx][tight][sum];
    int cnt = 0;
    int limit = (tight) ? s[idx] - '0' : 9;
    for(int i = 0; i <= limit; i++){
      int val = self(self, idx + 1, tight == 1 and s[idx] - '0' == i, (sum + i) % k);
      cnt += val;
      cnt %= MOD;
    }
    return dp[idx][tight][sum] = cnt;
  };
  
  int ans = dfs(dfs, 0, 1, 0);
  ans = (ans - 1 + MOD) % MOD;
  cout << ans;
}

int32_t main(){
  
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  
  int t = 1;
  // cin >> t;
  while(t--){
    solve();
  }
  return 0;
}


// Q2.
// Let's call some positive integer classy if its decimal representation contains no more than 3 non-zero digits. For example, numbers 4, 200000, 10203 are classy and numbers 4231, 102306, 727742000 are not.
// You are given a segment [L; R]. Count the number of classy integers x such that L ≤ x ≤ R.
// Each testcase contains several segments, for each of them you are required to solve the problem separately.

void solve(){
  int l, r;
  cin >> l >> r;
  --l;
  string a = to_string(l);
  string b = to_string(r);
  
  auto dfs = [&](auto &&self, int idx, bool tight, int cnt, string &s) -> int {
    if(idx == (int)s.size()){
      return 1;
    }
    if(dp[idx][tight][cnt] != -1) return dp[idx][tight][cnt];
    
    int limit = tight ? s[idx] - '0' : 9;
    int ans = 0;
    for(int i = 0; i <= limit; i++){
      if(i == 0){
        ans += self(self, idx + 1, tight and s[idx] - '0' == i, cnt, s);
      }
      else if(cnt <= 2){
        ans += self(self, idx + 1, tight and s[idx] - '0' == i, cnt + 1, s);
      }
    }
    return dp[idx][tight][cnt] = ans;
  };
  memset(dp, -1, sizeof(dp));
  int ans1 = dfs(dfs, 0, 1, 0, a);
  memset(dp, -1, sizeof(dp));
  int ans2 = dfs(dfs, 0, 1, 0, b);
  cout << ans2 - ans1 << endl;
  
}

int32_t main() 
{
  int t;
  cin >> t;
  while(t--){
    solve();
  }
  
  return 0;
}

// bitmask dp

// generating all subsets using dp

#include <bits/stdc++.h>
using namespace std;

int func(int pos, int mask, vector<vector<int>> &dp, int n){
    if(pos == n){
        return 1;
    }
    if(dp[pos][mask] != -1){
        return dp[pos][mask];
    }
    
    int val = 0;
    for(int i = 0; i < n; i++){
        if((mask & (1 << i)) == 0){
            val += func(pos + 1, mask | (1 << i), dp, n);
        }
    }
    return dp[pos][mask] = val;
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> dp(n, vector<int> ((1 << n), -1));
    cout << func(0, 0, dp, n);
    return 0;
} 
// Time Complexity: O(n * n * 2^n)
// Space Complexity: O(n * 2^n) for dp array + O(n) for recursion stack
