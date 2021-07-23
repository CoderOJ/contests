#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 2000005;
std::vector<int> e[N];
int n, m;

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n();
  for (int i=0; i<m; i++) {
    int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} 

int dep[N], fa[N];
void dfs0(int u, int f) {
  dep[u] = dep[f] + 1; fa[u] = f;
  for (int v: e[u]) if (!dep[v]) dfs0(v, u); }
// first: even, second odd
std::pair<int,int> upc[N], dwc[N];
void dfs1(int u) {
  upc[u] = dwc[u] = std::make_pair(0,0);
  for (int v: e[u]) {
    if (v == fa[u]) continue;
    if (dep[v] == dep[u] + 1) {
      dfs1(v); upc[u] += upc[v]; dwc[u] += dwc[v]; }
    else if (dep[v] > dep[u]) 
      ((dep[v] - dep[u]) % 2 ? upc[u].second : upc[u].first)++;
    else ((dep[u] - dep[v]) % 2 ? dwc[u].second : dwc[u].first)++; } 
  see(u, upc[u], dwc[u]); }

namespace bruteforce
{
void remove_edge(int u, int v) {
  for (auto it=e[u].begin(); it!=e[u].end(); ++it) 
    if (*it == v) { e[u].erase(it); break; }
  for (auto it=e[v].begin(); it!=e[v].end(); ++it) 
    if (*it == u) { e[v].erase(it); break; } }
void main() {
  std::vector<std::pair<int,int>> es;
  for (int u=1; u<=n; u++) for (int v: e[u]) if (dep[u] < dep[v]) {
    if (dep[v] - dep[u] != 1 || dwc[v] - upc[v] != std::make_pair(0,0))
      es.emplace_back(u,v); }
  long long ans = 0;
  for (const auto& i : es) { int u=i.first, v=i.second;
    see(u, v);
    remove_edge(u,v);
    for (int i=1; i<=n; i++) dep[i] = 0;
    dfs0(1, 0); dfs1(1);
    for (int u=2; u<=n; u++) 
      if (dwc[u].first - upc[u].first == dwc[1].first &&
          dwc[u].second - upc[u].second == 0) ans++;
    if (dwc[1].first == 1) ans++;
    e[u].push_back(v); e[v].push_back(u); }
  std::cout << ans / 2 << std::endl; }
}

void solve() 
{
  dfs0(1, 0); dfs1(1);
  if (dwc[1].first == 0) { puts("1"); return; }
  long long ans = 0;

  // single tree edge
  for (int u=2; u<=n; u++) 
    if (dwc[u].first - upc[u].first == dwc[1].first &&
        dwc[u].second - upc[u].second == 0)
      ans++;

  // single non-tree edge
  if (dwc[1].first == 1)
    ans++;

  if (ans) { printf("%lld\n", ans); return; }

  if (n <= 4000) { bruteforce::main(); return; }

  // two non-tree edges
  if (dwc[1].first == 2) 
    ans++;
  see("to non-tree edges", ans);

  // one tree edge and one non-tree edge
  for (int u=2; u<=n; u++) {
    const int leven = upc[u].first;
    const int reven = dwc[1].first - dwc[u].first;
    const int ceven = dwc[u].first - upc[u].first;
    const int codd  = dwc[u].second - upc[u].second;
    see(u, leven, reven,  ceven, codd);
    ans += leven + reven + std::min(ceven, codd) == 1;
  }
  see("one tree edge and one non-tree edge", ans);

  // two tree edges !!!
  

  printf("%lld\n", ans);
}
