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

constexpr int B = 20;
constexpr int N = 100005;
std::vector<std::pair<int,int>> e[N];
int n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i=0; i<n-1; i++) {
    int u=sc.n(), v=sc.n(); e[u].emplace_back(v,i); e[v].emplace_back(u,i); }
}

int dep[N], fa[N][B];
void dfs0(int u, int f) {
  dep[u] = dep[f] + 1; fa[u][0] = f;
  for (int i=0; i+1<B; i++) fa[u][i+1] = fa[fa[u][i]][i];
  for (const auto& [v,id] : e[u]) if (v != f) dfs0(v, u); }
int lca(int u, int v) {
  if (dep[u] < dep[v]) { std::swap(u, v); }
  int d = dep[u] - dep[v]; for (int i=0; i<B; i++) if (d & (1 << i)) u = fa[u][i];
  for (int i=B-1; i>=0; i--) if (fa[u][i] != fa[v][i]) { u=fa[u][i]; v=fa[v][i]; }
  return u==v ? u : fa[u][0]; }

int w[N], ans[N];
void dfs1(int u, int f) {
  for (const auto& [v,id] : e[u]) if (v != f) {
    dfs1(v, u); w[u] += w[v]; }
  for (const auto& [v,id] : e[u]) if (v == f) ans[id] = w[u]; }

void solve() 
{
  dfs0(1, 0);
  int m = sc.n();
  for (int i=0; i<m; i++) {
    int u=sc.n(), v=sc.n(), l=lca(u,v);
    w[l] -= 2; w[u]++; w[v]++; }
  dfs1(1, 0);
  for (int i=0; i<n-1; i++) printf("%d ", ans[i]);
}
