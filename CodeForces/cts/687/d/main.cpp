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
constexpr int M = N * (N - 1) / 2;
struct edge_t { int u,v,w,id; } e[M];
int n, m, q;

struct Dsu {
  int p[N * 2];
  void init() { for (int i=1; i<N*2; i++) p[i] = i; }
  int get(int u) {
    return u==p[u] ? u : p[u] = get(p[u]); }
  void merge(int u, int v) { p[get(u)] = get(v); }
} st;

void preInit() { } 
void init() 
{
  n = sc.n(); m = sc.n(); q = sc.n();
  for (int i=0; i<m; i++) e[i].u=sc.n(), e[i].v=sc.n(), e[i].w=sc.n(), e[i].id=i;
} 

void solve() 
{
  std::sort(e, e + m, [](auto x, auto y) { return x.w > y.w; }); 
  while (q--) {
    int l=sc.n()-1, r=sc.n();
    int ans = -1; st.init();
    for (int i=0; i<m; ++i) if (e[i].id >= l && e[i].id < r) {
      if (st.get(e[i].u) == st.get(e[i].v)) { ans = e[i].w; break; }
      else { st.merge(e[i].u, e[i].v+n); st.merge(e[i].v, e[i].u+n); } }
    printf("%d\n", ans); } 
}
