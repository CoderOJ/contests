#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 1000000007;
constexpr int N = 26;
int n, m, c;
int u[N * N], v[N * N], pow_c[N];
int dp[1 << N];

constexpr int M = 13;
constexpr int X = (1 << M) - 1;
int pops[1 << M];
inline int pop_cnt(int x) { return pops[x & X] + pops[x >> M]; }

inline int sub(int a) { return a >= MOD ? a - MOD : a; }

void preInit() { 
  pops[0] = 0;
  for (int i=1; i<=X; ++i) {
    pops[i] = pops[i >> 1] + (i & 1); } }
void init() {
  n = sc.n(); m = sc.n(); c = sc.n();
  for (int i=0; i<m; ++i) { u[i] = sc.n()-1; v[i]=sc.n()-1; }
} void solve() {
  dp[0] = 1;
  for (int i=0; i<m; ++i) {
    if (u[i] > v[i]) { std::swap(u[i], v[i]); }
    int ra = (1 << u[i]), rb = (1 << (v[i] - u[i] - 1)), rc = (1 << (n - v[i] - 1));
    int sb = u[i]+1, sc = v[i]+1;
    int muv = (1 << u[i]) | (1 << v[i]);
    for (int a=0; a<ra; ++a) for (int b=0; b<rb; ++b) for (int c=0; c<rc; ++c) {
      int x = a | (b << sb) | (c << sc); dp[x | muv] = sub(dp[x | muv] + dp[x]); } }
  int p_n = 1 << n;
  pow_c[0] = 1; 
  for (int i=1; i<=n; ++i) { pow_c[i] = (1ll * pow_c[i-1] * c) % MOD; }
  long long ans = 0;
  for (int i=0; i<p_n; ++i) {
    ans = (ans + 1ll * dp[i] * pow_c[pop_cnt(i) / 2]) % MOD; }
  printf("%lld\n", ans % MOD);
}
