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
// #define int long long

/** My code begins here **/

constexpr int N = 200005;
std::vector<int> e[N];
int val[N];
int n, k, root;

int size[N];
void dfs0(int u, int f) { size[u] = 1;
  for (int v: e[u]) if (v != f) { dfs0(v,u); size[u] += size[v]; } }

int dp[N], ans;
void dfs(int u, int f, int thr) {
  dp[u] = 1; int max0=0, max1=0; 
  for (int v: e[u]) if (v != f) {
    dfs(v, u, thr);
    if (dp[v] != size[v]) {
      if (dp[v]>max0) { std::swap(dp[v],max0); } 
      if (dp[v]>max1) { std::swap(dp[v],max1); } }
    else dp[u] += dp[v]; }
  dp[u] = val[u] < thr ? 0 : dp[u] + max0;
  checkMax(ans, dp[u] + max1); }

void preInit() {  } 
void init() 
{
  n = sc.n(); k = sc.n();
  for (int i=1; i<=n; i++) val[i] = sc.n();
  for (int i=1; i<n; i++) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} 

void solve() 
{
  root = static_cast<int>(std::min_element(val + 1, val + n + 1) - val);
  dfs0(root, 0);
  int l = *std::min_element(val+1, val+n+1);
  int r = *std::max_element(val+1, val+n+1);
  while (l < r) {
    int mid = (l + r + 1) / 2;
    ans = 0; dfs(root, 0, mid);
    if (ans >= k) { l = mid; }
    else { r = mid - 1; } }
  printf("%d\n", l);
}
