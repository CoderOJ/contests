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

const int N = 300005;
std::vector <std::pair<int,int>> e[N]; int n, s;
void preInit() { } void init() { n = sc.n(); s = sc.n(); rep (i,n-1) { int u=sc.n(), v=sc.n(), w=sc.n(); e[u].push_back(std::make_pair(v,w)); e[v].push_back(std::make_pair(u,w)); } }
int next[N]; int dfs0(int u, int f) { int max_dep=0; next[u] = -1; for (auto v: e[u]) if (v.first != f) { if (checkMax(max_dep, v.second + dfs0(v.first, u))) { next[u] = v.first; } } return max_dep; }
int find_last(int u) { return next[u] == -1 ? u : find_last(next[u]); }
std::set<int> on_chain; int ans = 0;
void dfs1(int u, int f, int dis) { checkMax(ans, dis); for (auto v: e[u]) if (v.first != f && !on_chain.count(v.first)) { dfs1(v.first, u, dis+v.second); } }

void solve() { 
  dfs0(1,0); int root = find_last(1); dfs0(root, 0);
  int u = root; while (u != -1) { on_chain.insert(u); u = next[u]; }
  for (int u: on_chain) { dfs1(u,0,0); } printf("%d\n", ans);
}
