#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/util.h"

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

constexpr int N = 2000005;
constexpr int C = 4;

struct offlineArray {
  long long a[N], add[N];
  inline void interval_add(int l, int r, long long delta) {
    add[l] += delta; add[r+1] -= delta; }
  inline void rebuild(int len) {
    for (int i=1; i<=len+2; ++i) { add[i] += add[i-1]; }
    for (int i=0; i<=len+2; ++i) { a[i] += add[i]; add[i] = 0; } }
  inline long long query(int pos) { return a[pos]; }
} st;

struct LCT {
  struct Node {
    Node *s[2]={nullptr, nullptr}, *f=nullptr;
    int val=0, assign=-1, len;

    inline bool is_root() {
      return f == nullptr || (f->s[0] != this && f->s[1] != this); }
    inline bool get_son() { return f->s[1] == this; }
    inline void push_assign(int val) { this->val = this->assign = val; }
    inline void push_down() {
      if (assign != -1) {
        if (s[0]) { s[0]->push_assign(assign); }
        if (s[1]) { s[1]->push_assign(assign); } 
        assign = -1; } }
    void push() {
      if (!is_root()) { f->push(); }
      push_down(); }
    inline void rotate() {
      Node *uu=this, *ff=f, *aa=ff->f; bool ss=get_son();
      if (!ff->is_root()) { aa->s[ff->get_son()] = uu; }
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff;
      if (ff->s[ss]) { ff->s[ss]->f = ff; } }
    void __splay() {
      if (is_root()) { return; }
      if (f->is_root()) { rotate(); return; }
      (get_son() == f->get_son() ? f : this) -> rotate(); rotate();
      __splay(); }
    void splay() { push(); __splay(); }
    void access(int val) {
      Node *uu=this, *ss=nullptr;
      while (uu) {
        uu->splay(); 
        if (uu->val >= val) { break; }
        uu->s[1] = ss;
        int fa_len = uu->f ? uu->f->len + 1 : 0;
        st.interval_add(fa_len, uu->len, val - uu->val);
        ss = uu; uu = uu->f; } 
      if (ss) { ss->push_assign(val); } }
  } *p;

  void set_fa(int u, int fa) { p[u].f = &p[fa]; }
  LCT() : p(new Node[N * 2]) {}
  ~LCT() { delete[] p; }
} T;

struct GSAM {
  struct Node {
    int next[C]={-1,-1,-1,-1}, link=-1, len=0, val=0;
  } *p;
  static constexpr int root = 0;
  int last = root, cnt = last + 1;

  GSAM() : p(new Node[N * 2]) {}
  bool setVal(int u, int val) {
    if (val <= p[u].val) { return false; }
    int delta = val - p[u].val; p[u].val = val;
    int l = p[u].link==-1 ? 0 : p[p[u].link].len+1, r = p[u].len;
    st.interval_add(l, r, delta); 
    return true; }

  void reset() { last = root; }
  void insert(std::size_t c) {
    { int q = p[last].next[c];
      if (q != -1) {
        if (p[q].len == p[last].len + 1) { last = q; }
        else {
          int clone = cnt++;
          p[clone] = p[q];
          p[clone].len = p[last].len + 1;
          p[q].link = clone;
          while (last != -1 && p[last].next[c] == q) {
            p[last].next[c] = clone; last = p[last].link; }
          last = clone; } 
        return; } }
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
      p[pos].next[c] = cur; pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else { int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    last = cur; }

  void build() {
    T.p[0].len = 0;
    for (int i=1;i<cnt;++i) {
      T.p[i].len = p[i].len; T.set_fa(i,p[i].link); } }

  ~GSAM() { delete[] p; }
} sam;

struct Operation {
  int type, val; char *pos;
} opt[N];

int n;
char s[N * 2];

void preInit() { } void init() {
  n = sc.n(); char *last = s;
  rep (i,n) {
    opt[i].type = sc.n(); opt[i].val = sc.n();
    if (opt[i].type == 1) { sc.next(last); opt[i].pos=last; last += std::strlen(last) + 1; } }
} void solve() {
  rep (i,n) if (opt[i].type == 1) {
    char *s_p = opt[i].pos;
    while(*s_p) { sam.insert(*s_p++ - 'a'); }
    sam.reset(); }
  sam.build();

  rep (i,n) {
    if (opt[i].type == 1) {
      char *s_p = opt[i].pos;
      int pos = GSAM::root, len=0;
      while (*s_p) {
        pos = sam.p[pos].next[*s_p++ - 'a']; len++;
        T.p[pos].access(opt[i].val); }
      st.rebuild(len); }
    else { printf("%lld\n", st.query(opt[i].val)); } }
}
