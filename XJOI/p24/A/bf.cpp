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
  { Brute::main(); }
}
