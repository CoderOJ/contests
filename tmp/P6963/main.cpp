#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
#include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 100005;

struct LCT {
  struct Node {
    Node *f=nullptr, *s[2] = {nullptr, nullptr};
    int val=0, tag=-1, min=0, max=0, rev=0;
    inline bool isRoot() const noexcept {
      return f == nullptr || (f->s[0] != this && f->s[1] != this); }
    inline bool getSon() const noexcept {
      return f->s[1] == this; }
    inline void pushUp() noexcept {
      min = max = val;
      if (s[0] != nullptr) { checkMin(min, s[0]->min); checkMax(max, s[0]->max); }
      if (s[1] != nullptr) { checkMin(min, s[1]->min); checkMax(max, s[1]->max); } }
    inline void pushRev() noexcept { std::swap(s[0], s[1]); rev ^= 1; }
    inline void pushAssign(int new_val) noexcept {
      val = min = max = tag = new_val; }
    inline void pushDown() noexcept {
      if (rev) {
        if (s[0] != nullptr) { s[0]->pushRev(); }
        if (s[1] != nullptr) { s[1]->pushRev(); } 
        rev = 0; }
      if (tag != -1) {
        if (s[0] != nullptr) { s[0]->pushAssign(tag); }
        if (s[1] != nullptr) { s[1]->pushAssign(tag); }
        tag = -1; } }
    void push() noexcept {
      if (!isRoot()) { f->push(); }
      pushDown(); }
    void rotate() noexcept {
      Node *const uu=this, *const ff=f, *const aa=ff->f; int ss=getSon();
      if (!ff->isRoot()) { aa->s[ff->getSon()] = uu; }
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff;
      if (ff->s[ss] != nullptr) { ff->s[ss]->f = ff; }
      ff->pushUp(); uu->pushUp(); }
    void _splay() noexcept {
      if (isRoot()) { return; }
      if (f->isRoot()) { rotate(); return; }
      (getSon() == f->getSon() ? f : this) -> rotate(); rotate();
      _splay(); }
    inline void splay() noexcept {
      push(); _splay(); }
    void access() noexcept {
      Node *uu = this, *ss = nullptr;
      while (uu != nullptr) {
        uu->splay(); uu->s[1] = ss; uu->pushUp();
        ss = uu; uu = uu->f; } }
    inline void makeroot() noexcept {
      access(); splay(); pushRev(); }
  } p[N];
  
  void link(int u, int v) {
    p[u].makeroot(); p[u].splay(); p[u].f = &p[v]; }
  void split(int u, int v) {
    p[u].makeroot(); p[v].access(); p[v].splay(); }
} T;

Tree::TreeLca<N> Td;
int n, f;

void preInit() { } void init() {
  n = sc.n(); f = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); T.link(u, v); Td.addEdge(u, v); }
  Td.initLca(1);
} void solve() { 
  std::vector<std::pair<int, std::pair<int, int>>> es(f);
  rep (i,f) { int u=sc.n(), v=sc.n(); es[i] = std::make_pair(-Td.dis(u,v), std::make_pair(u, v)); }
  std::sort(es.begin(), es.end()); 
  int ass_col = 1;
  for (const auto& e: es) {
    int u = e.second.first, v = e.second.second;
    T.split(u, v);
    // see(u, v); see(T.p[v].min, T.p[v].max);
    if (T.p[v].min != T.p[v].max) { puts("No"); return; }
    else { T.p[v].pushAssign(ass_col++); } }
  puts("Yes");
}
