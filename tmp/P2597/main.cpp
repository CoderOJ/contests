#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
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

const int N = 65536;
const int B = 16;
std::vector<int> e[N], e2[N];
int fa[N][B], dep[N], in[N], sz[N], n;

void preInit() { } void init() {
  n = sc.n();
  repa (i, n) { int u; while((u=sc.n()) != 0) { e[u].push_back(i); in[i]++; } }
} void solve() {

  std::function<int(int,int)> lca = [](int u, int v) -> int {
    if (dep[u] < dep[v]) { std::swap(u,v); }
    int d=dep[u]-dep[v]; rep (i,B) if ((d>>i)&1) { u=fa[u][i]; }
    repb (i,B-1,0) { if (fa[u][i] != fa[v][i]) { u=fa[u][i]; v=fa[v][i]; } }
    return u==v ? u : fa[u][0];
  };

  repa (i,n) fa[i][0] = -1;
  std::queue<int> que; 
  repa (i,n) if (in[i] == 0) { fa[i][0] = 0; que.push(i); }
  while (!que.empty()) { 
    int u = que.front(); que.pop();
    e2[fa[u][0]].push_back(u); dep[u] = dep[fa[u][0]] + 1;
    rep (i,B-1) fa[u][i+1] = fa[fa[u][i]][i];
    for (int v: e[u]) {
      if (fa[v][0] == -1) { fa[v][0] = u; }
      else { fa[v][0] = lca(fa[v][0], u); }
      in[v]--; if (in[v] == 0) { que.push(v); } } }

  std::function<void(int)> dfs = [&](int u) -> void {
    sz[u] = 1; for (int v: e2[u]) { dfs(v); sz[u] += sz[v]; } };

  dfs(0);
  repa (i,n) printf("%d\n", sz[i]-1);
}
