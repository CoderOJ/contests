#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"

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

constexpr int N = 600005;
struct Edge { int u, v, g; } e[N];
Edge *ops[N], **ops_end = ops + N, **ops_pos = ops_end, **ops_last = ops_pos;
int f[N], n, m;

void rebuild() {
  for (int *i=f+1; i<=f+n; ++i) { *i = 1; }
  for (Edge *i=e+1; i<e+n; ++i) { i->g = 0; }
  for (Edge **i=ops_pos; i<ops_end; ++i) {
    Edge *const p = *i; p->g = f[p->u] = f[p->v] = f[p->u] + f[p->v] - p->g; } 
  ops_last = ops_pos; }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  for (int i=1; i<n; ++i) {
    e[i].u = sc.n(); e[i].v = sc.n(); }
} void solve() {
  for (int *i=f+1; i<=f+n; ++i) { *i=1; }
  for (int i=0; i<m; ++i) {
    int opt = sc.n(), u = sc.n();
    if (opt == 1) {
      if (ops_pos != ops_last) { rebuild(); }
      printf("%d\n", f[u]); }
    else { *--ops_pos = &e[u]; } }
}
