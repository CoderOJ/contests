#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
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

constexpr int N = 200005;
constexpr int C = 26;

struct LCT {
  struct Node {
    Node *s[2]={nullptr,nullptr}, *f=nullptr;
    int wei=0, sum_wei=0, add=0;
    long long val=0, sum_val=0;
    inline bool is_root() {
      return f==nullptr || (f->s[0] != this && f->s[1] != this); }
    inline bool get_son() { return f->s[1] == this; }
    inline void push_up() {
      sum_wei = wei; sum_val = val;
      if (s[0]) { sum_wei += s[0]->sum_wei; sum_val += s[0]->sum_val; }
      if (s[1]) { sum_wei += s[1]->sum_wei; sum_val += s[1]->sum_val; } }
    inline void push_add(int del) { add += del; val += 1ll * wei * del; sum_val += 1ll * sum_wei * del; }
    inline void push_down() {
      if (s[0]) { s[0]->push_add(add); }
      if (s[1]) { s[1]->push_add(add); } 
      add = 0; }
    void push() { if (!is_root()) { f->push(); } push_down(); }
    void rotate() {
      Node *const uu=this, *const ff=f, *const aa=ff->f; bool ss = get_son();
      if (!ff->is_root()) { aa->s[ff->get_son()] = uu; }
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff;
      if (ff->s[ss]) { ff->s[ss]->f = ff; }
      ff->push_up(); uu->push_up(); }
    void _splay() {
      if (is_root()) { return; }
      if (f->is_root()) { rotate(); return; }
      (get_son() == f->get_son() ? f : this) -> rotate(); rotate(); 
      _splay(); }
    void splay() { push(); _splay(); }
    void access() {
      Node *uu=this, *ss=nullptr;
      while (uu != nullptr) {
        uu->splay(); uu->s[1] = ss; uu->push_up();
        ss = uu; uu = uu->f; } }
  } p[N * 2];

  void modify(int u, long long val) {
    p[u].access(); p[u].splay(); p[u].push_add(val); }
  auto query(int u) { 
    p[u].access(); p[u].splay(); return p[u].sum_val; }
} T;

struct SAM {
  struct Node {
    int next[C], link=-1, len=0;
    Node() { memset(next, -1, sizeof(next)); }
  } p[N * 2];
  static constexpr int root = 0;
  int last = root, cnt = last + 1;
  int pos[N];

  void insert(std::size_t c) {
    int cur = cnt++;
    pos[ p[cur].len = p[last].len + 1 ] = cur;
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
      p[pos].next[c] = cur; pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else { int q = p[pos].next[c]; 
      if (p[q].len == p[pos].len + 1) {
        p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[cur].link = p[q].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    last = cur; }

  void build() {
    for (int i: range(1,cnt)) {
      T.p[i].f = &T.p[p[i].link]; 
      T.p[i].wei = p[i].len - p[p[i].link].len; } }
} sam;

int n, q, a[N], b[N];
char s[N];

void preInit() { } void init() {
  n = sc.n(); q = sc.n(); sc.next(s);
} void solve() {
  std::reverse(s, s+n);
  for (int i: range(n)) { sam.insert(s[i] - 'a'); } sam.build();
  for ([[maybe_unused]] int _case: range(q)) {
    int n=sc.n(), m=sc.n();
    for (int i: range(n)) { a[i] = ::n - sc.n() + 1; }
    for (int i: range(m)) { b[i] = ::n - sc.n() + 1; }
    for (int i: range(n)) { T.modify(sam.pos[a[i]], 1); }
    long long ans = 0;
    for (int i: range(m)) { ans += T.query(sam.pos[b[i]]); }
    printf("%lld\n", ans);
    for (int i: range(n)) { T.modify(sam.pos[a[i]], -1); } 
  }
}
