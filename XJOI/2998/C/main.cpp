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
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
constexpr int N = 500005;
using Int = Temps::Intm<MOD>;
std::vector<int> e[N];
int n;

Int pinv[N];
void preInit() 
{  
  pinv[1] = 1;
  for (int i = 2; i < N; i++)
    pinv[i] = pinv[MOD % i] * (MOD - MOD / i);
  std::partial_sum(pinv, pinv + N, pinv);
} 

void init() 
{
  n = sc.n();
  for (int i = 1; i < n; i++)
  {
    int u = sc.n(), v = sc.n();
    e[u].push_back(v); e[v].push_back(u);
  }
} 

int dep[N], fa[N], leaf_cnt[N];
void dfs0(int u, int f)
{
  dep[u] = dep[f] + 1; fa[u] = f; leaf_cnt[u] = (e[u].size() == 1);
  for (int v: e[u]) if (v != f) dfs0(v, u), leaf_cnt[u] += leaf_cnt[v];
}

int dfs1(int u, int f, int d, int gd)
{
  if (d == gd) return 1;
  int res = 0;
  for (int v: e[u]) if (v != f) res += dfs1(v, u, d + 1, gd);
  return res;
}

void solve() 
{
  dfs0(1, 0);
  int root = static_cast<int>(std::max_element(dep, dep + n + 1) - dep);
  dfs0(root, 0);

  int dlen = *std::max_element(dep, dep + n + 1);
  std::vector<int> grp;

  if (dlen % 2 == 1)
  {
    int up_step = dlen / 2;
    int u = static_cast<int>(std::max_element(dep, dep + n + 1) - dep);
    for (int i = 0; i < up_step; i++) u = fa[u];
    for (int v: e[u]) grp.push_back(dfs1(v, u, 1, up_step));
  }
  else
  {
    int up_step = dlen / 2 - 1;
    int u = static_cast<int>(std::max_element(dep, dep + n + 1) - dep);
    for (int i = 0; i < up_step; i++) u = fa[u];
    grp = std::vector<int>{dfs1(u, fa[u], 0, up_step), dfs1(fa[u], u, 0, up_step)};
  }

  int tot = std::accumulate(grp.begin(), grp.end(), 0);
  Int ans = 0;
  for (int x : grp)
    ans += pinv[tot - x];
  ans -= Int(grp.size() - 1) * pinv[tot];

  std::cout << ans * leaf_cnt[root] << std::endl;
}
