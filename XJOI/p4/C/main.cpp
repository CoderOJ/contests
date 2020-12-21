#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
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

constexpr int N = 100005;

struct GraphBase {
  int n; 
  void init(int _n) { n=_n; }
  virtual void addEdge(int u, int v)=0; };

struct Graph : GraphBase {
  std::vector<int> e[N];
  virtual void addEdge(int u, int v) override {
    e[u].push_back(v); e[v].push_back(u); }
};

struct GraphTcc : public Graph {
  int bel[N], dfn[N], low[N], dfn_cnt=1, bel_cnt=1;
  std::stack<int> group;
  GraphTcc() { memset(dfn, -1, sizeof(dfn)); } 
  void dfs(int u, int f) {
    dfn[u] = dfn_cnt++; low[u] = dfn[u]; group.push(u);
    bool fa_protect = true;
    for (int v: e[u]) {
      if (v == f && fa_protect) { fa_protect=false; continue; }
      if (dfn[v] == -1) { dfs(v, u); }
      checkMin(low[u], low[v]); }
    if (low[u] == dfn[u]) {
      int this_bel = bel_cnt++;
      while (group.top() != u) { 
        bel[ group.top() ] = this_bel;
        group.pop(); }
      bel[ group.top() ] = this_bel;
      group.pop(); } }
  void solve(GraphBase& output) {
    repa (i,n) if (dfn[i] == -1) { dfs(i,0); }
    output.init(bel_cnt - 1);
    repa (u,n) for (int v: e[u]) { 
      int bu=bel[u], bv=bel[v];
      if (bu < bv) { output.addEdge(bu,bv); } } }
};

struct TreeLCT : public GraphBase {
  static constexpr int N = 200005;
  struct LCT_impl {
    struct Node {
      Node *s[2] = {nullptr, nullptr}, *f = nullptr;
      int val=0, val_sum=0, wei, wei_sum, add=-1, rev=0;
      Node (int wei=0) : wei(wei), wei_sum(wei) {}
      bool isRoot() {
        if (f == nullptr) return 1;
        return !(f->s[0]==this || f->s[1]==this); }
      void pushAdd(int del) {
        val = del*wei; val_sum = del*wei_sum; add = del; }
      void pushRev() { rev^=1; std::swap(s[0], s[1]); }
      void pushDown() {
        if (rev) {
          if (s[0] != nullptr) { s[0]->pushRev(); }
          if (s[1] != nullptr) { s[1]->pushRev(); } 
          rev = 0; }
        if (add != -1) {
          if (s[0] != nullptr) { s[0]->pushAdd(add); }
          if (s[1] != nullptr) { s[1]->pushAdd(add); }
          add = -1; } }
      void pushUp() {
        val_sum = val; wei_sum = wei;
        if (s[0] != nullptr) { val_sum += s[0]->val_sum; wei_sum += s[0]->wei_sum; }
        if (s[1] != nullptr) { val_sum += s[1]->val_sum; wei_sum += s[1]->wei_sum; } }
      void push() {
        if (!isRoot()) { f->push(); } 
        pushDown(); }
      bool getSon() { return f->s[1] == this; }
      void rotate() {
        Node *uu=this, *ff=f, *aa=ff->f; bool ss=getSon(); 
        if (!ff->isRoot()) aa->s[ ff->getSon() ] = uu;
        ff->f = uu; ff->s[ss] = uu->s[!ss];
        uu->f = aa; uu->s[!ss] = ff;
        if (ff->s[ss] != nullptr) { ff->s[ss]->f = ff; }
        ff->pushUp(); uu->pushUp(); }
      void _splay() { 
        if (isRoot()) { return; }
        if (f->isRoot()) { rotate(); return; } 
        ( getSon() == f->getSon() ? f : this ) -> rotate(); rotate();
        _splay(); }
      Node* splay() { push(); _splay(); return this; }
      void access() {
        Node *uu=this, *ss=nullptr; 
        while (uu!=nullptr) {
          uu->splay(); uu->s[1]=ss; uu->pushUp();
          ss = uu; uu = uu->f; } }
      void makeRoot() { access(); splay(); pushRev(); }
      Node* findRoot() {
        access(); splay(); pushDown(); Node* uu=this;
        while (uu->s[0] != nullptr) { uu = uu->s[0]; uu->pushDown(); } 
        return uu; }
    };

    Node p[N];
    void split(int u, int v) {
      p[u].makeRoot(); p[v].access(); p[v].splay(); }
    void link(int u, int v) {
      p[u].makeRoot(); p[u].f = &p[v]; }
    void cut(int u, int v) {
      split(u,v);
      p[v].s[0] = p[u].f = nullptr; p[v].pushUp(); }
    bool isUni(int u, int v) {
      return p[u].findRoot() == p[v].findRoot(); }
  } T;

  std::queue<int> free_node;
  TreeLCT () { 
    constexpr int free_begin = 100001;
    constexpr int free_end = 200000;
    repi (i,free_begin,free_end) free_node.push(i); }
  inline int newNode() { 
    int res = free_node.front(); free_node.pop(); return res; }
  inline void deleteNode(int u) {
    T.p[u] = LCT_impl::Node(); free_node.push(u); }

  int relay = -1;
  virtual void addEdge(int u, int v) override final { 
    slog("adding edge (%d,%d)\n", u,v);
    relay = newNode(); T.p[relay].wei = 1; T.p[relay].val = 1;
    T.link(u,relay); T.link(relay,v); }
  void cutEdge(int u, int v, int relay) {
    T.cut(u,relay); T.cut(relay,v); deleteNode(relay); }
  struct trace_type { int u,v, relay; enum Type { link, add } type; };
  int query(std::vector< std::pair<int,int> >extra_edge, int s, int t) {
    std::stack<trace_type> trace;
    for (auto pos: extra_edge) {
      trace_type tp;
      int u = pos.first, v = pos.second; tp.u=u; tp.v=v;
      if (T.isUni(u,v)) {
        tp.type = trace_type::add; 
        T.split(u,v); T.p[v].pushAdd(0); }
      else {
        tp.type = trace_type::link;
        addEdge(u,v); tp.relay = relay; }
      trace.push(tp); }
    int res = -1;
    if (T.isUni(s,t)) { T.split(s,t); res = T.p[t].val_sum; }
    while (!trace.empty()) {
      auto tp = trace.top(); trace.pop(); int u=tp.u, v=tp.v;
      if (tp.type == trace_type::add) {
        T.split(u,v); T.p[v].pushAdd(1); }
      else { cutEdge(u,v, tp.relay); } }
    return res; }
};

GraphTcc Go;
TreeLCT Gs;
int n, m, q;

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  Go.init(n);
  rep (i,m) { int u=sc.n(), v=sc.n(); Go.addEdge(u,v); }
  Go.solve(Gs);
} void solve() {
  q = sc.n();
  while (q--) {
    int s=sc.n(), t=sc.n(), k=sc.n();
    s = Go.bel[s]; t = Go.bel[t];
    slog("answering query (s=%d,t=%d,k=%d)\n",s,t,k);
    std::vector< std::pair<int,int> > extra_edge;
    rep (i,k) { int u=sc.n(), v=sc.n(); 
      extra_edge.push_back( std::make_pair(Go.bel[u],Go.bel[v]) ); }
    printf("%d\n", Gs.query(extra_edge, s, t)); }
}
