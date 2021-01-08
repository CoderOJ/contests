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

struct LCT {
  struct Node {
    Node *s[2]={nullptr, nullptr}, *f=nullptr;
    int rev=0, vt=1, at=1;
    inline bool isRoot() { 
      if (f == nullptr) { return 1; }
      return f->s[0] != this && f->s[1] != this; }
    inline bool getSon() { return f->s[1] == this; }
    inline void pushRev() { std::swap(s[0], s[1]); rev ^= 1; }
    inline void pushDown() {
      if (rev) { 
        if (s[0] != nullptr) { s[0]->pushRev(); }
        if (s[1] != nullptr) { s[1]->pushRev(); } }
      rev = 0; }
    inline void pushUp() {
      at = vt;
      if (s[0] != nullptr) { at += s[0]->at; }
      if (s[1] != nullptr) { at += s[1]->at; } }
    void push() { if (!isRoot()) { f->push(); } pushDown(); }
    void rotate() { 
      int ss = getSon(); Node *uu=this, *ff=f, *aa=ff->f;
      if (!ff->isRoot()) { aa->s[ ff->getSon() ] = uu; }
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff; 
      if (ff->s[ss] != nullptr) { ff->s[ss]->f = ff; }
      ff->pushUp(); uu->pushUp(); }
    void _splay() {
      if (isRoot()) { return; }
      if (f->isRoot()) { rotate(); return; }
      (getSon() == f->getSon() ? f : this)->rotate(); rotate();
      _splay(); }
    Node* splay() { push(); _splay(); return this; }
    void access() {
      Node *u = this, *s = nullptr;
      while (u != nullptr) {
        u->splay(); 
        if (u->s[1] != nullptr) { u->vt += u->s[1]->at; }
        if (s != nullptr) { u->vt -= s->at; }
        u->s[1] = s; u->pushUp();
        s = u; u = u->f; } }
    void makeRoot() { access(); splay(); pushRev(); }
    Node* findRoot() {
      access(); splay(); 
      Node* u = this; u->pushDown(); 
      while (u->s[0] != nullptr) {
        u = u->s[0]; u->pushDown(); }
      return u->splay(); }
  } p[N];
  std::set<int> e[N];

  void link(int u, int v) {
    if (p[u].findRoot() == p[v].findRoot()) {
      puts("ILLEGAL"); return; }
    e[u].insert(v); e[v].insert(u); puts("OK");
    p[u].makeRoot(); p[v].makeRoot();
    p[u].f = &p[v]; p[v].vt += p[u].at; p[v].pushUp(); }
  void cut(int u, int v) {
    if (!e[u].count(v)) { puts("ILLEGAL"); return; }
    puts("OK");
    e[u].erase(v); e[v].erase(u);
    p[u].makeRoot(); p[v].access(); p[v].splay();
    p[u].f = p[v].s[0] = nullptr; p[v].pushUp(); }
  void query(int u, int v) {
    if (p[u].findRoot() != p[v].findRoot()) { puts("ILLEGAL"); return; }
    p[u].makeRoot(); p[u].access();
    int res = p[u].vt; p[v].access(); printf("%d.0000\n", res - p[v].vt); }
} T;

int q;

void preInit() { } void init() {
  sc.n(); q=sc.n();
} void solve() {
  while (q--) {
    int opt=sc.n(), u=sc.n(), v=sc.n(); 
    if (opt == 0) { T.link(u,v); }
    else if (opt == 1) { T.cut(u,v); }
    else { T.query(u,v); } }
}
