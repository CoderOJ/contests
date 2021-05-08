#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
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

constexpr int N = 100005;
constexpr int B = 30;

int n, m, q;
int eu[N], ev[N], ew[N];
int ql[N], qr[N],  qu[N], qv[N];

struct Basis {
  int a[N];
  void insert(int x) {
    // see("insert", x);
    for (int i=B-1; i>=0; i--) if (x & (1 << i)) {
      if (a[i]) { x ^= a[i]; }
      else { a[i] = x; break; } } }
  int query_max(int x) {
    for (int i=B-1; i>=0; i--) 
      checkMax(x, x ^ a[i]);
    return x; } 
  void clear() { memset(a, 0, sizeof(a)); } };


namespace q1
{

struct LCTNode {
  LCTNode *f = nullptr;
  LCTNode *s[2] = {nullptr, nullptr};
  bool rev = false;
  int val = 0, sum = 0;

  bool is_root();
  bool get_son();
  void push_up();
  void reverse();
  void push_down();
  void push();
  void rotate();
  void splay();
  void access();
  void make_root();
  LCTNode *find_root();
};

bool LCTNode::is_root() {
  return f == nullptr || 
         (f->s[0] != this && f->s[1] != this);
}

bool LCTNode::get_son() {
  return this == f->s[1];
}

void LCTNode::push_up() {
  sum = val;
  if (s[0] != nullptr) sum ^= s[0]->sum;
  if (s[1] != nullptr) sum ^= s[1]->sum;
}

void LCTNode::reverse() {
  rev = !rev;
  std::swap(s[0], s[1]);
}

void LCTNode::push_down() {
  if (rev) {
    if (s[0] != nullptr) s[0]->reverse();
    if (s[1] != nullptr) s[1]->reverse();
    rev = false;
  }
}

void LCTNode::push() {
  if (!is_root()) f->push();
  push_down();
}

void LCTNode::rotate() {
  LCTNode *const uu=this, *ff=f, *aa=ff->f;
  bool ss = uu->get_son();
  if (!ff->is_root()) aa->s[ff->get_son()] = uu;
  ff->f = uu, ff->s[ss] = uu->s[!ss];
  uu->f = aa; uu->s[!ss] = ff;
  if (ff->s[ss] != nullptr) ff->s[ss]->f = ff;
  ff->push_up(), uu->push_up(); 
}

void LCTNode::splay() {
  push();
  while (!is_root()) {
    if (f->is_root()) {
      rotate();
      return;
    }
    (get_son() == f->get_son() ? f : this)->rotate();
    rotate(); 
  }
}

void LCTNode::access() {
  LCTNode *uu = this, *ss = nullptr;
  while (uu != nullptr) {
    uu->splay();
    uu->s[1] = ss;
    uu->push_up();
    ss = uu;
    uu = uu->f;
  }
}

void LCTNode::make_root() {
  access();
  splay();
  reverse();
}

LCTNode *LCTNode::find_root() {
  access();
  splay();
  LCTNode *uu = this;
  uu->push_down();
  while (uu->s[0] != nullptr) {
    uu = uu->s[0];
    uu->push_down();
  }
  uu->splay();
  return uu;
}

void link(LCTNode *const u, LCTNode *const v) {
  u->make_root();
  u->splay();
  u->f = v;
}

void split(LCTNode *const u, LCTNode *const v) {
  u->make_root();
  v->access();
  v->splay();
}

void cut(LCTNode *u, LCTNode *v) {
  split(u, v);
  v->s[0] = u->f = nullptr;
  v->push_up();
}

LCTNode p[N * 2];

bool valid() {
  for (int i=0; i<q; ++i) if (ql[i] != 1) { return false; }
  return true; }

struct Querys { int r, u, v, id; };
Querys qs[N];
int ans[N], ptop;
Basis bs;

void link(int u, int v, int w) {
  if (p[u].find_root() == p[v].find_root()) {
    split(&p[u], &p[v]);
    bs.insert(p[v].sum ^ w); }
  else {
    int rid = ptop++; p[rid].val = w;
    link(&p[u], &p[rid]); link(&p[rid], &p[v]); } }

void main() {
  for (int i=0; i<q; ++i) qs[i] = { qr[i], qu[i], qv[i], i };
  std::sort(qs, qs+q, [](const Querys& a, const Querys& b) { return a.r < b.r; });
  ptop = n + 1; int qtop = 0;
  for (int i=0; i<q; ++i) {
    while (qtop < qs[i].r) { link(eu[qtop], ev[qtop], ew[qtop]); qtop++; }
    if (p[qs[i].u].find_root() != p[qs[i].v].find_root()) { ans[qs[i].id] = -1; }
    else { split(&p[qs[i].u], &p[qs[i].v]); ans[qs[i].id] = bs.query_max(p[qs[i].v].sum); } }
  for (int i=0; i<q; ++i) printf("%d\n", ans[i]); }

} /* namespace q1 */

struct Edge { int v, w, id; };

Basis bs;
std::vector<Edge> e[N];
int vis[N], sum[N], gl, gr;


void dfs(int u, int f) {
  vis[u] = true;
  for (const auto& i: e[u]) if (i.v != f && i.id >= gl && i.id <= gr) {
    if (vis[i.v]) { bs.insert(i.w ^ sum[u] ^ sum[i.v]); }
    else { sum[i.v] = sum[u] ^ i.w; dfs(i.v, u); } } }

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); q = sc.n();
  for (int i=0; i<m; ++i) {
    int u = sc.n(), v = sc.n(), w = sc.n();
    eu[i] = u, ev[i] = v, ew[i] = w;
    e[u].push_back({v, w, i+1}); e[v].push_back({u, w, i+1}); }
  for (int i=0; i<q; ++i) {
    ql[i] = sc.n(), qr[i] = sc.n(), qu[i] = sc.n(), qv[i] = sc.n(); }
} void solve() {
  if (q1::valid()) { q1::main(); return; }
  for (int i=0; i<q; ++i) {
    int l = ql[i], r = qr[i], u = qu[i], v = qv[i];
    gl = l, gr = r; memset(vis, false, sizeof(vis)); memset(sum, 0, sizeof(sum)); bs.clear();
    dfs(u, 0); printf("%d\n", vis[v] ? bs.query_max(sum[v]) : -1); }
}
