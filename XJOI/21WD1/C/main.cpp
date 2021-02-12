#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 300005;
constexpr int C = 26;

struct LCT {
  struct Node {
    Node *f=nullptr, *s[2] = {nullptr, nullptr};
    int val=0, tag=0, rev=0;
    inline bool isRoot() const noexcept {
      return f == nullptr || (f->s[0] != this && f->s[1] != this); }
    inline bool getSon() const noexcept {
      return f->s[1] == this; }
    inline void pushRev() noexcept { std::swap(s[0], s[1]); rev ^= 1; }
    inline void pushAdd(int _val) noexcept { val += _val; tag += _val; }
    inline void pushDown() noexcept {
      if (rev) {
        if (s[0] != nullptr) { s[0]->pushRev(); }
        if (s[1] != nullptr) { s[1]->pushRev(); } 
        rev = 0; }
      if (tag != 0) {
        if (s[0] != nullptr) { s[0]->pushAdd(tag); }
        if (s[1] != nullptr) { s[1]->pushAdd(tag); }
        tag = 0; } }
    void push() noexcept {
      if (!isRoot()) { f->push(); }
      pushDown(); }
    void rotate() noexcept {
      Node *const uu=this, *const ff=f, *const aa=ff->f; int ss=getSon();
      if (!ff->isRoot()) { aa->s[ff->getSon()] = uu; }
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff;
      if (ff->s[ss] != nullptr) { ff->s[ss]->f = ff; } }
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
        uu->splay(); uu->s[1] = ss; 
        ss = uu; uu = uu->f; } }
    inline void makeroot() noexcept {
      access(); splay(); pushRev(); }
  } p[N * 2];
  
  void link(int u, int v) {
    slog("link (%d, %d)", u, v);
    p[u].makeroot(); p[u].splay(); p[u].f = &p[v]; }
  void split(int u, int v) {
    p[u].makeroot(); p[v].access(); p[v].splay(); }
  void cut(int u, int v) {
    slog("cut (%d, %d)", u, v);
    split(u, v); p[v].s[0] = p[u].f = nullptr; }
  void set(int u) { 
    p[0].makeroot(); p[u].access(); p[u].splay(); }
} T;

struct SAM {
  struct Node {
    int next[C], link=-1, len=0;
    Node() { memset(next, -1, sizeof(next)); }
  } p[N * 2];

  static constexpr int root = 0;
  int last = root, cnt = root + 1;
  int endpos[N];

  void insert(std::size_t c) noexcept {
    int cur = cnt++, pos = last;
    endpos[ p[cur].len = p[last].len + 1 ] = cur;
    while (pos != -1 && p[pos].next[c] == -1) {
      p[pos].next[c] = cur; pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; T.link(root, cur); }
    else { int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) {
        p[cur].link = q; T.link(q, cur); }
      else { int clone = cnt++, qf = p[q].link;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[q].link = p[cur].link = clone;
        T.cut(qf, q); T.link(qf, clone); T.link(clone, q); T.link(clone, cur);
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    T.set(cur); T.p[cur].pushAdd(1);
    last = cur; }

  int query(int len) {
    int pos = endpos[len];
    T.set(pos); return T.p[pos].val; }
} SAM;

int n;

void preInit() { } void init() {
  scanf("%d", &n);
} void solve() {
  int lastans = 0;
  int nn = 0;
  while (n--) {
    char opt[5];
    scanf("%s",opt);
    if (opt[0] == 'a') { nn++;
      char _c; scanf(" %c ", &_c);
      std::size_t c = ((std::size_t)(_c - 'a') + lastans) % 26;
      see(c);
      SAM.insert(c); }
    else {
      int len; scanf("%d", &len);
      len = (len - 1 + lastans) % nn + 1;
      printf("%d\n", lastans = SAM.query(len)); }
  }
}
