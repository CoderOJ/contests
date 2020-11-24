#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

const int N = 100005;

struct LCT {
  struct Node {
    Node *s[2], *f;
    int val, tot, tag;

    Node (Node *f=nullptr, int val=0) : f(f), val(val), tot(val), tag(0) {}
    bool isRoot() {
      if (f==nullptr) return true;
      return f->s[0] != this && f->s[1] != this; }
    void pushUp() {
      tot = val;
      if (s[0]!=nullptr) tot ^= s[0]->tot;
      if (s[1]!=nullptr) tot ^= s[1]->tot; }
    void pushAdd(int del) {
      val ^= del; tot ^= del; tag ^= del; }
    void pushDown() {
      if (s[0] != nullptr) s[0]->pushAdd(tag);
      if (s[1] != nullptr) s[1]->pushAdd(tag);
      tag = 0; }
    void push() {
      if (!isRoot()) f->push();
      pushDown(); }
    bool getSon() {
      return f->s[1] == this; }
    void rotate() {
      Node *uu=this, *ff=f, *aa=ff->f;
      int ss = getSon();
      if (!ff->isRoot()) aa->s[ ff->getSon() ] = uu;
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff;
      if (ff->s[ss] != nullptr) ff->s[ss]->f = ff;
      ff->pushUp(); uu->pushUp(); }
    void _splay() {
      if (isRoot()) return;
      if (f->isRoot()) { rotate(); return; }
      ( getSon() == f->getSon() ? f : this ) -> rotate(); rotate();
      _splay(); }
    void splay() {
      push(); _splay(); }
    void access() {
      Node *uu=this, *ss=nullptr;
      while (uu!=nullptr) {
        uu->splay(); uu->s[1] = ss; uu->pushUp();
        ss = uu; uu = uu->f; } }
    void split() {
      access(); splay(); }
  };

  Node p[N];
} T;

int pre_yes = 0;
int n, m;

std::vector <int> e[N];
int fa[N], a[N];

void preInit()
{

}

void dfs(int u, int f) {
  fa[u] = f;
  for (int v: e[u]) if (v!=f) { dfs(v,u); } }

void init()
{
  n = sc.n(); m = sc.n()+1;
  repa (i,n) a[i] = sc.n() % m;
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
  dfs(1,0);
  repa (i,n) if (fa[i] != 0) {
    T.p[i].f = &T.p[ fa[fa[i]] ]; }
  repa (i,n) {
    T.p[i].split();
    T.p[i].pushAdd( a[i] ); }
}

void solve()
{
  int q = sc.n();
  while (q--) {
    int opt = sc.n();
    if (opt == 1) {
      int u = fa[ sc.n() ^ pre_yes ];
      T.p[u].split();
      int pend = T.p[u].val ^ a[u];
      see(u, pend);
      if (pend != 0) {
        puts("Yes");
        pre_yes++; }
      else { puts("No"); } }
    else if (opt == 2) {
      int u = sc.n() ^ pre_yes, val = sc.n() ^ pre_yes;
      T.p[u].split();
      int delta = T.p[u].val ^ val;
      T.p[u].pushAdd(delta); }
    else if (opt == 3) {
      int u=sc.n()^pre_yes, v=sc.n()^pre_yes, w= (sc.n()^pre_yes) % m;
      a[v] = w;
      fa[v] = u; 
      T.p[v].f = &T.p[ fa[fa[v]] ]; 
      T.p[v].split(); T.p[v].pushAdd(w); }
  }
}
