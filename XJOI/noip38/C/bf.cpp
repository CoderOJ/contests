
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

const int N = 50005;
std::vector<int> e[N];
std::pair<int, int> es[N];
int n,m;

int mark[N];
bool dfs(int u, int f, int goal) {
  if (u == goal) { mark[u]++; return 1; }
  bool res = 0;
  for (int v: e[u]) if (v!=f) { res |= dfs(v,u,goal); }
  if (res) { mark[u]++; } 
  return res; }

bool intersect(std::pair<int, int> a, std::pair<int, int> b) {
  memset(mark, 0, sizeof(mark));
  dfs(a.first, 0, a.second); dfs(b.first, 0, b.second);
  repa (i,n) if (mark[i] >= 2) { return 1; }
  return 0;
}

bool valid(int mask) {
  rep (i,m) if ((mask>>i) & 1) rep (j,m) if ((mask>>j) & 1) if (i!=j) {
    if (intersect(es[i], es[j])) { return 0; } }
  return 1;
}

int popCnt(int u) {
  int res = 0;
  rep (i,m) if ((u>>i) & 1) { res++; }
  return res; }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
  rep (i,m) { es[i].first = sc.n(); es[i].second = sc.n(); }
} void solve() {
  int ans = 0;
  rep (mask, (1<<m)) {
    if (valid(mask)) {
      see(mask);
      checkMax(ans, popCnt(mask)); } }
  printf("%d\n", ans);
}
