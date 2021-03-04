#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 1000000007;
typedef Temps::Intm<Temps::ConstModuler<MOD>> Int;
constexpr int N = 100005;

struct Dsu {
  int p[N];
  Dsu() { for (int i: range(N)) p[i]=i; }
  int get(int u) { return u==p[u] ? u : p[u] = get(p[u]); }
  void merge(int u, int v) { p[get(u)] = get(v); }
} loves;

Temps::Vector<std::pair<int,int>> elove, ehate;
Temps::Vector<int> e[N];
int n, m, col[N];

void preInit() { } void init() {
  n = sc.n(); m = sc.n();

  for ([[maybe_unused]] int _: range(m)) {
    int u=sc.n(), v=sc.n(), c=sc.n();
    (c ? elove : ehate).push_back({u,v}); }
} void solve() {
  auto add_edge = [](const int u, const int v) {
    e[u].push_back(v); e[v].push_back(u); };
  for (const auto& [u,v]: elove) { loves.merge(u,v); }    
  for (const auto& [u,v]: ehate) { add_edge(loves.get(u), loves.get(v)); }

  std::function<bool(int)> valid_graph = [&](int u) -> bool {
    for (const int v: e[u]) {
      if (col[v] != -1) {
        if (col[v] == col[u]) { return false; } }
      else { col[v] = !col[u]; if (!valid_graph(v)) { return false; } } }
    return true; };

  std::fill(col+1, col+n+1, -1);
  Int ans = 1;
  for (const int _u: range(1,n+1)) {
    const int u = loves.get(_u);
    if (col[u] == -1) { col[u] = 0;
      if (!valid_graph(u)) { ans = 0; break; }
      else { ans *= 2; } } }

  printf("%d\n", static_cast<int>(ans / 2));
}
