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

struct STree {
  struct Node {
    Node *l, *r;
    int val;
    Node() : l(nullptr), r(nullptr), val(0) {}
    void pushUp() {
      val = 0;
      if (l!=nullptr) checkMax(val, l->val);
      if (r!=nullptr) checkMax(val, r->val); }
    ~Node() { delete l; delete r; }
  };
  
  Node* R;
  STree() : R(nullptr) {}
  void modify(int l, int r, int p, int val, Node* &u) {
    if (u == nullptr) { u = new Node(); }
    if (l == r) { u->val++; return; }
    int mid = (l+r) / 2;
    if (p <= mid) { modify(l,mid, p,val, u->l); }
    else { modify(mid+1,r, p,val, u->r); }
    u->pushUp(); }
  int query(int l, int r, Node* u) {
    if (l == r) { return l; }
    int mid = (l+r)/2;
    if (u->l == nullptr || u->l->val < u->val) { return query(mid+1,r,u->r); }
    else { return query(l,mid,u->l); } }
  void merge(int l, int r, Node* &u, Node* &v) {
    if (v == nullptr) { return; }
    if (u == nullptr) { u = v; v = nullptr; return; }
    if (l == r) { u->val += v->val; delete v; v = nullptr; return; }
    int mid = (l+r) / 2;
    merge(l,mid,u->l,v->l); merge(mid+1,r,u->r,v->r); 
    u->pushUp(); 
    delete v; v = nullptr; }
  ~STree() { delete R; }
};

const int N = 1000005;
std::vector<int> e[N];
STree st[N];
int ans[N], n;

void dfs(int u, int f, int dep=1) {
  for (int v: e[u]) if (v!=f) { dfs(v,u,dep+1); st[u].merge(1,n, st[u].R, st[v].R); }
  st[u].modify(1,n,dep,1, st[u].R);
  ans[u] = st[u].query(1,n,st[u].R) - dep; }

void preInit() { } void init() {
  n = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  dfs(1,0);
  repa (i,n) { printf("%d\n", ans[i]); }
}
