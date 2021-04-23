#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
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

#define long long long
constexpr int N = 300005;

std::set<int> pos[N];
int pre[N], suf[N];
int a[N], n, m;

struct FTree {
  static constexpr int OFFSET = 5;
  long a[N + OFFSET], tot=0;
  static inline int low(int u) { return u & (-u); }
  void modify(int u, long del) {
    u += OFFSET; tot += del;
    while (u < N + OFFSET) {
      a[u] += del; u += low(u); } }
  long query(int u) {
    u += OFFSET;
    long res = 0;
    while (u) {
      res += a[u]; u -= low(u); } 
    return res; }
};

namespace lc_tot {

FTree l2c, l2c_tl;
void modify(int u, long del) {
  slog("lc_tot: modify [%d] += %lld", u, del);
  l2c.modify(u, del); 
  l2c_tl.modify(u, del * u); }
long query(long thr) {
  return (l2c.tot - l2c.query(thr)) * thr + l2c_tl.query(thr); }

} /* namespace lc_tot */

namespace suf_tot {

FTree stc, stc_tl;
void modify(int u, long val) {
  stc.modify(u, val);
  stc_tl.modify(u, val * u); }
long query(int thr) {
  return (stc_tl.tot - stc_tl.query(thr-1)) - (thr-1) * (stc.tot - stc.query(thr-1)); }

} /* namespace suf_tot */

std::pair<int,int> pre_suf(int u) {
  int w = a[u];
  std::set<int>::iterator it = pos[w].find(u);
  std::pair<int, int> res(-1, n);
  auto itp = it, its = it;
  if (itp != pos[w].begin()) res.first = *(--itp);
  if (++its != pos[w].end()) res.second = *its;
  return res; }

void set_pre(int u, int val) {
  if (u < 0 || u >= n) return;
  lc_tot::modify(u-pre[u], -1);
  pre[u] = val;
  lc_tot::modify(u-pre[u], 1);
}

void set_suf(int u, int val) {
  if (u < 0 || u >= n) return;
  if (suf[u] == n) { suf_tot::modify(u, -1); }
  suf[u] = val;
  if (suf[u] == n) { suf_tot::modify(u, 1); }
}

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  for (int i=0; i<n; ++i) a[i] = sc.n();
} void solve() {
  for (int i=0; i<n; ++i) pos[a[i]].insert(i);
  for (int i=0; i<n; ++i) {
    auto ps = pre_suf(i);
    pre[i] = ps.first, suf[i] = ps.second; 
    lc_tot::modify(i-pre[i], 1);
    if (suf[i] == n) suf_tot::modify(i, 1); }

  while (m--) {
    int opt = sc.n();
    if (opt == 1) {
      int x=sc.n()-1, w=sc.n();
      auto ps_ori = pre_suf(x); pos[a[x]].erase(x);
      set_suf(ps_ori.first, ps_ori.second);
      set_pre(ps_ori.second, ps_ori.first);

      a[x] = w; pos[a[x]].insert(x); 
      auto ps_pos = pre_suf(x);
      see(ps_pos);
      set_pre(x, ps_pos.first);
      set_suf(x, ps_pos.second); 
      set_suf(ps_pos.first, x);
      set_pre(ps_pos.second, x); }
    else {
      int k = sc.n();
      see(lc_tot::query(k), suf_tot::query(n-k+1));
      printf("%lld\n", lc_tot::query(k) - suf_tot::query(n-k+1)); }
  }
}
