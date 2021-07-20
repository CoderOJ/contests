#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define int long long

/** My code begins here **/

constexpr int N = 100005;

struct dp_t {
  int ss=0, sub_sr=0, ss_sr=0;
  dp_t() =default;
  dp_t(int val) : ss(val), sub_sr(val), ss_sr(val) {}
};

std::vector<int> e[N];
int n, w[N], ans = 0;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i=1; i<=n; i++) w[i] = sc.n();
  for (int i=1; i<n; i++) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} 

dp_t dp[N];
void dfs(int u, int f) {
  dp[u] = dp_t(w[u]); 
  int pre_v_sub_sr = 0;
  for (int v: e[u]) if (v != f) {
    dfs(v, u); const dp_t& dv = dp[v]; dp_t du;
    du.ss = std::max(dp[u].ss, w[u] + dv.ss);
    du.sub_sr = std::max({dp[u].sub_sr, dp[u].ss + dv.ss, dv.sub_sr});
    du.ss_sr = std::max({dp[u].ss_sr, dp[u].ss + dv.sub_sr, pre_v_sub_sr + w[u] + dv.ss, dv.ss_sr + w[u]});
    pre_v_sub_sr = std::max(pre_v_sub_sr, dv.sub_sr);
    ans = std::max({ans, dp[u].sub_sr + dv.sub_sr, dp[u].ss_sr + dv.ss, dp[u].ss + dv.ss_sr});
    dp[u] = du; } }

void solve() 
{
  dfs(1, 0);
  printf("%lld\n", ans);
}
