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


constexpr int B = 22;
constexpr int N = 300005;

template <class T>
struct FTree
{
  std::vector<T> a; size_t N;
  FTree() =default;
  FTree(size_t n) : a(n + 5, T()) , N(n + 5) {}
  static int low(int u) { return u & -u; }
  void modify(int u, int det) { u += 5;
    for (; u<(int)N; u += low(u)) a[(size_t)u] += det; }
  void modify(int l, int r, int det) { if (l > r) return;
    modify(l,det); modify(r,-det); }
  T query(int u) { u += 5; T res = T();
    for (; u; u -= low(u)) res += a[(size_t)u];
    return res; }
  T query(int l, int r) { return l <= r ? query(r) - (l>=0 ? query(l) : T()) : T(); }
};

std::vector<int> eo[N];
std::tuple<int,int,int> es[N * 2];
int n, m, q;

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n(); q = sc.n();
  for (int i = 0; i < m; i++) {
    int u = sc.n(), v = sc.n(), w = sc.n();
    eo[u].push_back(v);  eo[v].push_back(u);
    es[i] = std::make_tuple(u, v, w); }
} 

std::vector<int> e[N * 2];
int od[N], ofa[N], sp_cnt;
bool ohave_f[N];
void dfs0(int u, int f)
{
  ofa[u] = f;
  for (int v: eo[u]) if (v != f) {
    if (od[v] == -1) { od[v] = od[u] + 1; dfs0(v, u); }
    else if (od[v] < od[u]) {
      const int sp = sp_cnt++;
      e[v].push_back(sp);
      for (int p = u; p != v; p = ofa[p]) {
        e[sp].push_back(p), ohave_f[p] = true; } } }
  if (ohave_f[u] == false)
    e[f].push_back(u);
}

int d[N * 2], fa[N * 2][B], dl[N * 2], dr[N * 2], dfn, ord[N * 2];
void dfs1(int u, int f)
{
  see(u, f);
  dl[u] = dfn++;
  d[u] = d[f] + 1; fa[u][0] = f;
  for (int i = 0; i + 1 < B; i++)
    fa[u][i + 1] = fa[fa[u][i]][i];
  int ord_cnt = 0;
  for (int v: e[u]) dfs1(v, u), ord[v] = ord_cnt++;
  dr[u] = dfn++;
}
int up(int u, int d)
{
  for (int i = 0;  i < B; i++) if (d & (1 << i)) u = fa[u][i];
  return u;
}
int lca(int u, int v)
{
  if (d[u] < d[v]) std::swap(u, v);
  int delta = d[u] - d[v]; for (int i=0; i<B; i++) if (delta & (1 << i)) u = fa[u][i];
  for (int i = B-1; i>=0; i--) if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; }
  return u == v ? u : fa[u][0];
}

FTree<int> smin(N*4), smax(N*4), sall(N*4), sons[N*2];
void modify(int u, int v, int det)
{
  if (d[u] > d[v]) std::swap(u, v);
  if (d[u] == d[v] - 1)
  {
    smin.modify(dl[v], dr[v], det);
    smax.modify(dl[v], dr[v], det);
    sall.modify(dl[v], dr[v], det);
  }
  else if (d[u] == d[v])
  {
    int ur = fa[u][0];
    int s = static_cast<int>(e[ur].size());
    auto modify = [ur, det](auto& T, int l, int r)
    { T.modify(dl[e[ur][(size_t)l]], dr[e[ur][(size_t)r]], det); };

    if (ord[u] > ord[v]) std::swap(u, v);
    assert(ord[u] + 1 == ord[v]);

    sons[ur].modify(ord[v], det);
    modify(smax, 0, std::min(s/2-1, ord[u]));
    modify(smax, std::max(s/2, ord[v]), s-1);
    modify(smin, ord[v], s/2-1);
    modify(smin, s/2, ord[u]);
    modify(sall, 0, s-1);
  }
  else // d[u] == d[v] - 2
  {
    int ur = fa[v][0];
    int s = static_cast<int>(e[ur].size());
    auto modify = [ur, det](auto& T, int l, int r)
    { T.modify(dl[e[ur][(size_t)l]], dr[e[ur][(size_t)r]], det); };
    assert(ord[v] == 0 || ord[v] == s - 1);

    if (ord[v] == 0) { modify(smin, 0, s/2-1); modify(smax, s/2, s-1); sons[ur].modify(0, det); }
    else             { modify(smax, 0, s/2-1); modify(smin, s/2, s-1); sons[ur].modify(s, det); }
    modify(sall, 0, s-1);
  }
}

std::vector<std::pair<int,int>> l2q[N*2];
std::pair<int,int> qcnt[N*2];
void clear(int u)
{
  l2q[u].clear();
  qcnt[u] = {0,0};
}

void solve() 
{
  memset(od, -1, sizeof(od)); od[1] = 0; 
  sp_cnt = n + 1;
  dfs0(1, 0);
  dfs1(1, 0);
  for (int i = n+1; i < sp_cnt; i++)
    sons[i] = FTree<int>(e[i].size() + 1);

  for (int i = 0; i < m; i++) std::apply(modify, es[i]);
  
  for (int i = 0; i < q; i++)
  {
    int k = sc.n();

    int ans = 0;
    if (k)
    {
      std::vector<int> us, cs;
      for (int i = 0; i < k; i++)
      {
        int u=sc.n(), v=sc.n(), type=sc.n(), l = lca(u, v);
        int lu = l > n ? up(u, d[u] - d[l] - 1) : l;
        int lv = l > n ? up(v, d[v] - d[l] - 1) : l;
        see(u, v, type, l, lu, lv);
        if (type == 0) { qcnt[u].first++, qcnt[v].first++, qcnt[lu].first--; qcnt[lv].first--; }
        else { qcnt[u].second++, qcnt[v].second++, qcnt[lu].second--; qcnt[lv].second--; }
        us.push_back(u); us.push_back(v); us.push_back(lu); us.push_back(lv); us.push_back(l);
        if (l > n)
        {
          int ql = ord[lu], qr = ord[lv];
          if (ql > qr) std::swap(ql, qr);
          assert(ql != qr);
          int clen = qr - ql, rlen = static_cast<int>(e[l].size()) + 1 - clen;
          if ((clen < rlen) ^ type) { l2q[l].push_back({ql+1, qr}); }
          else { l2q[l].push_back({0,ql}); l2q[l].push_back({qr+1, static_cast<int>(e[l].size())}); }
        }
      }

      auto calc_path = [&ans](int u, int f)
      {
        qcnt[f] += qcnt[u];
        const auto cnt = qcnt[u];
        see(u, f, cnt);
        if (u > n) u = fa[u][0];
        if (f > n) 
        {
          int uf = up(u, d[u] - d[f] - 1);
          const int csize = static_cast<int>(e[f].size()) + 1;
          const int lc = ord[uf] + 1, rc = csize - lc;
          int minl=0, minr=lc-1, maxl=lc, maxr=csize-1;
          if (lc > rc) { std::swap(minl, maxl); std::swap(minr, maxr); }
          if (cnt.first) { l2q[f].push_back({minl,minr}); }
          if (cnt.second) { l2q[f].push_back({maxl,maxr}); }
          f = uf;
        }
        see(u, f, cnt);
        [[maybe_unused]] const int pans = ans;
        if (cnt.first && cnt.second) { ans += sall.query(dl[f], dl[u]); }
        else if (cnt.first) { ans += smin.query(dl[f], dl[u]); }
        else if (cnt.second) { ans += smax.query(dl[f], dl[u]); }
        see(ans - pans);
      };
      std::sort(us.begin(), us.end(), [](int x, int y) { return dl[x] < dl[y]; });
      us.erase(std::unique(us.begin(), us.end()), us.end());
      static int stack[N*2]; int *ps = stack;
      {
        int lall = lca(us[0], us.back());
        if (us[0] != lall) *ps++ = lall;
      }
      for (int u: us)
      {
        cs.push_back(u);
        while (ps - stack >= 2) {
          int l = lca(ps[-1], u);
          if (d[l] <= d[ps[-2]]) { calc_path(ps[-1], ps[-2]); ps--; }
          else if (d[l] < d[ps[-1]]) { cs.push_back(l); calc_path(ps[-1], l); ps[-1] = l; }
          else break; }
        *ps++ = u;
      }
      while (ps - stack >= 2) {
        calc_path(ps[-1], ps[-2]);
        ps--; }
      slog("chain ans = %d", ans);

      std::sort(cs.begin(), cs.end());
      cs.erase(std::unique(cs.begin(), cs.end()), cs.end());
      for (int u: cs) if (u > n)
      {
        std::sort(l2q[u].begin(), l2q[u].end());        
        int last = 0;
        for (const auto& [l,r] : l2q[u]) {
          see(u, l, r);
          ans += sons[u].query(std::max(last, l)-1, r);
          checkMax(last, r + 1); }
      }

      for (int u: cs) clear(u);
    }
    printf("%d\n", ans);

    int p=sc.n()-1, d=sc.n();
    if (p != -1) 
    { 
      modify(std::get<0>(es[p]), std::get<1>(es[p]), d - std::get<2>(es[p]));
      std::get<2>(es[p]) = d;
    }
  }
}
