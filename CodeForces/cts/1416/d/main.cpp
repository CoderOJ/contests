#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

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

constexpr int N = 500005;
struct Opteration { int opt, u; } opt[N];
std::multiset<int> *st[N], st_pool[N], *stp_top = st_pool;
Vector<int> small_part[N], e[N];
int u[N], v[N], is_cut[N];
int size[N], id[N];
int p[N], p2u[N], n, m, q;

int get_id(int u) { 
  return id[u]==u ? u : id[u] = get_id(id[u]); }

void dfs(Vector<int> &output, int u, int f) {
  output.push_back(u);
  for (int v: e[u]) if (v != f) dfs(output, v, u); }

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); q = sc.n();
  for (int i=1; i<=n; ++i) { p[i] = sc.n(); p2u[p[i]] = i; }
  for (int i=1; i<=m; ++i) { u[i] = sc.n(); v[i] = sc.n(); }
  for (int i=0; i<q; ++i) { opt[i].opt = sc.n(); opt[i].u = sc.n(); }
} void solve() {
  for (int i=0; i<q; ++i) if (opt[i].opt == 2) { is_cut[opt[i].u] = true; }
  for (int i=1; i<=n; ++i) { id[i]=i; size[i]=1; }

  for (int i=1; i<=m; ++i) if (!is_cut[i]) {
    int tu = u[i], tv = v[i];
    int pu = get_id(u[i]), pv = get_id(v[i]);
    if (pu == pv) continue;
    if (size[pu] > size[pv]) { std::swap(pu, pv); }
    id[pu] = pv; size[pv] += size[pu]; 
    e[tu].push_back(tv); e[tv].push_back(tu); }

  for (int i=q-1; i>=0; --i) if (opt[i].opt == 2) {
    int tu = u[opt[i].u], tv = v[opt[i].u];
    int pu = get_id(tu), pv = get_id(tv);
    if (pu == pv) continue;
    if (size[pu] > size[pv]) { std::swap(pu, pv); }
    id[pu] = pv; size[pv] += size[pu]; dfs(small_part[i], pu, 0); 
    e[tu].push_back(tv); e[tv].push_back(tu); }

  for (int i=1; i<=n; ++i) if (id[i] == i) { st[i] = stp_top++; st[i]->insert(p[i]); }
  for (int i=1; i<=n; ++i) if (id[i] != i) { st[i] = st[get_id(i)]; st[i]->insert(p[i]); }
  
  for (int i=0; i<q; ++i) {
    if (opt[i].opt == 1) {
      see(opt[i].u, *st[opt[i].u]);
      int ans = st[opt[i].u]->empty() ? 0 : *st[opt[i].u]->rbegin();
      printf("%d\n", ans); 
      if (ans) { st[opt[i].u]->erase(ans); p[p2u[ans]] = 0; } }
    else {
      if (small_part[i].empty()) continue;
      const auto stp = stp_top++, sto = st[small_part[i][0]];
      for (int v: small_part[i]) {
        see(v);
        if (p[v]) { sto->erase(p[v]); stp->insert(p[v]); }
        st[v] = stp; } } }
}
