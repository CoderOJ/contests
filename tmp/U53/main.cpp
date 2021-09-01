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

constexpr int N = 500005;

#pragma pack(1)
struct node_t
{
  node_t *s[2] = {nullptr, nullptr}, *f = nullptr;
  std::pair<int,int> val, min;

  bool is_root() { return f == nullptr || (f->s[0] != this && f->s[1] != this); }
  bool get_son() { return f->s[1] == this; }
  void push_up() { min = val; 
    if (s[0]) { checkMin(min, s[0]->min); } if (s[1]) { checkMin(min, s[1]->min); } }
  void rotate() { node_t *uu=this, *ff=f, *aa=ff->f; bool ss=get_son();
    if (!ff->is_root()) aa->s[ff->get_son()] = uu;
    ff->f = uu; ff->s[ss] = uu->s[!ss]; uu->f = aa; uu->s[!ss] = ff;
    if (ff->s[ss]) ff->s[ss]->f = ff; 
    ff->push_up(); }
  void splay() {
    while (!is_root()) { if (f->is_root()) { rotate(); break; } 
      (f->get_son() == get_son() ? f : this)->rotate(); rotate(); } push_up(); }
  node_t *access() { node_t *uu=this, *ss=nullptr;
    while (uu) { uu->splay(); uu->s[1] = ss; uu->push_up(); ss = uu; uu = uu->f; } 
    return ss; }
  node_t *access_to(node_t *end) { node_t *uu=this, *ss=nullptr;
    while (uu && uu >= end) { uu->splay(); uu->s[1] = ss; uu->push_up(); ss = uu; uu = uu->f; } 
    return ss; }
} __attribute__((aligned(1)));

node_t p[N];
int w[N], fa[N], n, k;

int lca(int u, int v)
{
  p[u].access();
  return static_cast<int>(p[v].access() - p);
}

int get_min_vertex(int u, int f)
{
  p[u].access_to(&p[f]);
  p[f].splay(); 
  return p[f].s[1]->min.second;
}

using path_t = std::pair<int,int>;
#pragma pack(1)
struct paths_t { path_t a, b, c; } __attribute__((aligned(1)));
auto get_paths(int a, int b, int c)
{
  int lab = lca(a, b), lac = lca(a, c), lbc = lca(b, c);
  if (lab == lac)       return paths_t{path_t(a, fa[lab]), path_t(b, lab), path_t(c, lbc)};
  else if (lab == lbc)  return paths_t{path_t(b, fa[lab]), path_t(a, lab), path_t(c, lac)};
  else                  return paths_t{path_t(c, fa[lbc]), path_t(a, lac), path_t(b, lab)};
}
paths_t path[N];

void preInit() {  } 
void init() 
{
  n = sc.n(); k = sc.n();
  for (int i = 1; i <= n; i++) w[i] = sc.n();
  for (int i = 2; i <= n; i++) fa[i] = sc.n();
  for (int i = 1; i <= n; i++) 
  {
    p[i].val = p[i].min = std::make_pair(w[i], i);
    p[i].f = &p[fa[i]];
  }
  for (int i = 1; i <= n; i++) path[i] = get_paths(sc.n(), sc.n(), sc.n());
} 

#pragma pack(1)
struct ppath_t
{
  int w;
  unsigned long long u : 20;
  unsigned long long pu : 20;
  unsigned long long pf : 20;
  ppath_t(int u, int w, int pu, int pf) : w(w), u(u), pu(pu), pf(pf) {}
  bool operator< (const ppath_t &rhs) const { return w > rhs.w; }
} __attribute__ ((aligned(1)));

void solve() 
{
  std::priority_queue<ppath_t> que;
  for (int u = 1; u <= n; u++)
    que.push({u, w[u], u, fa[u]});

  for (int i = 0; i < k; i++)
  {
    auto push = [&](int u, int w, int pu, int pf) { que.push({u, w, pu, pf}); };

    auto uu = que.top(); int u=uu.u, w=uu.w, pu=uu.pu, pf=uu.pf; que.pop(); printf("%d\n", w); 
    if (pu != u) { int v = get_min_vertex(pu, u); push(v, w + ::w[v] - ::w[u], pu, u); }
    if (u != pf && fa[u] != pf) { int v = get_min_vertex(fa[u], pf); push(v, w + ::w[v] - ::w[u], fa[u], pf); }
    auto [p1, p2, p3] = path[u];
    auto [p1u, p1f] = p1; if (p1u != p1f) { int v = get_min_vertex(p1u, p1f); push(v, w + ::w[v], p1u, p1f); }
    auto [p2u, p2f] = p2; if (p2u != p2f) { int v = get_min_vertex(p2u, p2f); push(v, w + ::w[v], p2u, p2f); }
    auto [p3u, p3f] = p3; if (p3u != p3f) { int v = get_min_vertex(p3u, p3f); push(v, w + ::w[v], p3u, p3f); }
  }

}
