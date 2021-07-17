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

constexpr int N = 1005;
constexpr int M = 200005;
struct edge_t { int u,v; } e[M];
struct query_t { int u, v, l, r, id; } qs[M];
int dis[N][N];
int n, m, q;

void preInit() {  } 
void init() 
{ n = sc.n(); m = sc.n(); q = sc.n();
  for (int i=0; i<m; ++i) e[i].u = sc.n(), e[i].v = sc.n();
  for (int i=0; i<q; ++i) qs[i].l=sc.n()-1, qs[i].r=sc.n(), qs[i].u=sc.n(), qs[i].v=sc.n(), qs[i].id=i; } 

bool ans[M];
void solve() 
{
  memset(dis, 0x3f, sizeof(dis)); 
  std::sort(qs, qs + q, [](const auto& a, const auto& b) { return a.l > b.l; });

  auto update = [](int u, int v, int t) {
    dis[u][v] = dis[v][u] = t;
    for (int s=1; s<=n; ++s) {
      checkMin(dis[v][s], dis[u][s]);
      checkMin(dis[u][s], dis[v][s]); } };
  int last = m - 1;
  for (int i=0; i<q; ++i) {
    const auto& [u,v,l,r,id] = qs[i];
    for (; last>=l; last--) update(e[last].u, e[last].v, last);  
    ans[id] = dis[u][v] < r ? true : false; }
  for (int i=0; i<q; ++i) puts(ans[i] ? "Yes" : "No");
}
