#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/pipe.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
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

using namespace Temps;

constexpr int N = 5005;
std::mt19937 rd(20050610);
int dep[N], n, fa[N];

void ask(int u, std::set<int> sub) {
  if (sub.count(u)) sub.erase(u);
  for (int v: sub) if (dep[v] == dep[u] + 1) fa[v] = u;

  Vector<int> gss = Vector<int>(sub) | ranges::filter([u](int v) { return dep[v] > dep[u] + 1; });
  if (gss.size() == 0) return;
  int heavy_v = gss[static_cast<unsigned int>(rd()) % gss.size()];
  int heavy = -1;
  for (int v: sub) if (dep[v] == dep[u] + 1) { 
    std::cout << "? 1 " << v << " " << heavy_v << std::endl;
    int d; std::cin >> d; if (dep[heavy_v] - dep[v] == d) { heavy = v; break; } }
  if (heavy == -1) { return; }

  Vector<int> ots;
  for (int v: sub) if (dep[v] == dep[u] + 1 && v != heavy) {
    std::cout << "? 2 " << v << std::endl;
    int cnt; std::cin >> cnt;
    std::set<int> next;
    for (int i=0; i<cnt; ++i) {
      int a; std::cin >> a; next.insert(a); ots.push_back(a); }
    ask(v, next); }
  for (int v: ots) sub.erase(v);
  ask(heavy, sub); }

void preInit() { } void init() {
  scanf("%d", &n);
} void solve() {
  for (int i=2; i<=n; ++i) {
    std::cout << "? 1 1 " << i << std::endl;
    std::cin >> dep[i]; }
  std::set<int> full(range(1, n+1).begin(), range(1, n+1).end());
  ask(1, full);
  std::cout << "!";
  for (int i=2; i<=n; ++i) std::cout << " " << fa[i];
}
