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

const int N = 200005;
std::vector<int> e[N];
std::set<int> st[N];
int sz[N], pref[N], n;

void dfs0(int u, int f) {
  sz[u] = 1; pref[u] = -1; int max_son = 0;
  for (int v: e[u]) if (v!=f) { 
    dfs0(v,u); sz[u] += sz[v];
    if (checkMax(max_son, sz[v])) { pref[u] = v; } } }

int ans = 0x3f3f3f3f;
void merge(std::set<int>& A, const std::set<int>& B) { for (int i: B) A.insert(i); }
void update_ans(int a, int b) { 
  int c = n - a - b;  
  checkMin(ans, std::max( std::abs(a-b), std::max( std::abs(a-c), std::abs(b-c) ) ) ); }
void dfs1(int u, int f) {
  for (int v: e[u]) if (v!=f) { dfs1(v,u); }
  if (pref[u] != -1) st[u] = std::move(st[pref[u]]);
  for (int v: e[u]) if (v!=f && v!=pref[u]) { merge(st[u], st[v]); }
  int upper_size = n - sz[u];
  int key = (sz[u]+1) / 2;
  auto try_1 = st[u].lower_bound(key);
  if (try_1 != st[u].end()) { update_ans(upper_size, *try_1); }
  if (try_1 != st[u].begin()) { --try_1; update_ans(upper_size, *try_1); } 
  st[u].insert(sz[u]); 
}

std::set<int> pres;
void dfs2(int u, int f) {
  int key = (n-sz[u]+1) / 2;
  auto try_1 = pres.lower_bound(key);
  if (try_1 != pres.end()) { update_ans(sz[u], *try_1); }
  if (try_1 != pres.begin()) { --try_1; update_ans(sz[u], *try_1); }
  for (int v: e[u]) if (v!=f) { dfs2(v,u); }
  pres.insert(sz[u]); }

void preInit() { } void init() {
  n = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() { 
  dfs0(1,0);
  dfs1(1,0);
  dfs2(1,0);
  printf("%d\n", ans);
}
