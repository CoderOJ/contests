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

constexpr int N = 100005;
std::vector<int> e[N];
int origin_state[N], n, m;
struct Query { int opt, u, d; } qs[N];

namespace Rooted {
int check() {
  int u = -2;
  rep (i,m) if (qs[i].opt == 2 && qs[i].u != u) {
    if (u == -2) { u = qs[i].u; }
    else { return -1; } }
  return u;
}

struct FTree {
  static constexpr int OFFSET = 5;
  int a[N + OFFSET];
  static inline int low(int u) { return u & (-u); }
  void modify(int p, int v) { p += OFFSET;
    while (p < N) { a[p] += v; p += low(p); } }
  int query(int p) { p += OFFSET;
    int res = 0;
    while (p) { res += a[p]; p -= low(p); }
    return res; }
} dep_cnt;
int state[N], fa[N], dep[N], son_black[N];
void dfs(int u, int f) {
  fa[u] = f;  dep[u] = dep[f] + 1;
  for (int v: e[u]) if (v != f) { dfs(v, u); } } 
void revert(int u) {
  int del = state[u] == 0 ? 1 : -1;
  state[u] ^= 1; son_black[fa[u]] += del;
  if (state[fa[u]] == 0) { dep_cnt.modify(dep[u], del); }
  dep_cnt.modify(dep[u] + 1, -del * son_black[u]); }
void main(int root) {
  dep[0] = -1; dfs(root, 0);
  repa (i,n) if (origin_state[i]) { revert(i); }
  rep (i,m) { const Query& q = qs[i];
    if (q.opt == 1) { revert(q.u); }
    else { 
      int if_change = false;
      if (state[q.u] == 1) { revert(q.u); if_change = true; }
      printf("%d\n", dep_cnt.query(q.d));
      if (if_change) { revert(q.u); } } }
}
} /* Rooted */

namespace Brute {
int state[N];
int dfs(int u, int f, int d) {
  int ans = (state[u] == 1 && state[f] == 0);
  if (d) for (int v: e[u]) if (v != f) {
    ans += dfs(v, u, d-1); }
  return ans; }
void main() {
  memcpy(state, origin_state, sizeof(*state) * (n + 1));
  state[0] = 1;
  rep (i,m) { const Query& q = qs[i];
    if (q.opt == 1) { state[q.u] ^= 1; }
    else { 
      int b_s = state[q.u]; state[q.u] = 0;
      printf("%d\n", dfs(q.u, 0, q.d)); 
      state[q.u] = b_s; } }
}
} /* Brute */

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
  repa (i,n) origin_state[i] = sc.nextChar() - '0';
  rep (i,m) { qs[i].opt = sc.n(); qs[i].u = sc.n(); if (qs[i].opt == 2) { qs[i].d = sc.n(); } }
} void solve() {
  int same_u = Rooted::check();
  if (same_u == -2) { return; }
  else if (same_u != -1) { Rooted::main(same_u); }
  else { Brute::main(); }
}
