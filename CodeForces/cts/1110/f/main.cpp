#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

#include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 500005;
std::vector<std::pair<int,int>> e[N];
int n, q;

struct Query { int l, r, id; };
Vector<Query> qs[N];

constexpr long long inf = 0x3f3f3f3f3f3f3f3f;
Temps::STree<Temps::STreeNode::NodeAddMin<long long>> sgt(N);
long long  ans[N];
int ul[N], ur[N];

void dfs0(int u, int f, long long dep) {
  ul[u] = u, ur[u] = u + 1;
  if (e[u].size() == 0) { sgt.modify(u, u+1, dep); }
  else { sgt.modify(u, u+1, inf); }
  for (const auto& [v,w]: e[u]) if (v != f) { 
    dfs0(v, u, dep + w); checkMax(ur[u], ur[v]); } }

void dfs1(int u, int f, long long global_offset) {
  for (const auto& [l,r,id] : qs[u]) {
    ans[id] = sgt.query(l, r + 1).min + global_offset; }
  for (const auto& [v, w]: e[u]) if (v != f) {
    see(w, -2 * w);
    sgt.modify(ul[v], ur[v], -2 * w);
    dfs1(v, u, global_offset + w); 
    sgt.modify(ul[v], ur[v],  2 * w); } }

void preInit() { } void init() {
  n = sc.n(), q = sc.n();
  for (int i=2; i<=n; ++i) { int fa = sc.n(), w = sc.n(); e[fa].emplace_back(i, w); }
  for (int i=0; i<q; ++i) { int u=sc.n(), l=sc.n(), r=sc.n(); qs[u].push_back({l, r, i}); }
} void solve() {
  dfs0(1, 0, 0); dfs1(1, 0, 0);
  for (int i=0; i<q; ++i) printf("%lld\n", ans[i]);
}
