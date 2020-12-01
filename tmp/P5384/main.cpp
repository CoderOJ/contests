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

const int N = 1000005;

struct STree {
  struct Node {
    int _l, _r;
    int val;
    Node (int _l=-1, int _r=-1, int val=0) : _l(_l), _r(_r), val(val) {}
  };

  static const int POOL_SIZE = N * 2;
  static Node pool[POOL_SIZE];
  static int pool_cnt;
  static int newNode() { return pool_cnt++; }
  static Node* gp(int a) { return pool + a; }

  int R;
  STree () { R = -1; }
  void modify(int l, int r, int p, int val, int &u) {
    if (u == -1) { u = newNode(); }
    if (l == r) { gp(u)->val += val; return; }
    int mid = (l+r) / 2;
    if (p <= mid) modify(l,mid, p,val, gp(u)->_l);
    else modify(mid+1,r, p,val, gp(u)->_r); }
  int query(int l, int r, int p, int &u) {
    if (u == -1) { u = newNode(); }
    if (l == r) { return gp(u)->val; }
    int mid = (l+r) / 2;
    if (p <= mid) return query(l,mid,p,gp(u)->_l);
    else return query(mid+1,r,p,gp(u)->_r); }
  int merge(int l, int r, int u, int v) {
    if (u == -1) { return v; }
    if (v == -1) { return u; }
    gp(u)->val += gp(v)->val;
    int mid = (l+r) / 2;
    gp(u)->_l = merge(l,mid,gp(u)->_l,gp(v)->_l);
    gp(u)->_r = merge(mid+1,r,gp(u)->_r,gp(v)->_r);
    return u; }
  STree& operator = (STree&& B) { R = B.R; B.R = -1; return *this; }
};

STree::Node STree::pool[STree::POOL_SIZE];
int STree::pool_cnt = 0;

std::vector<int> e[N], qid[N], pid[N];
struct Query { int u,p,k,ans; } qs[N];
STree st[N];
int n, q, max_dep=0;

std::vector<int> ancs;
void dfs(int u, int dep) {
  checkMax(max_dep, dep);
  ancs.push_back(u);
  for (int i: qid[u]) { 
    if (qs[i].k < (int)ancs.size()) { qs[i].p = ancs[ancs.size()-qs[i].k-1]; }
    else { qs[i].p = u; qs[i].k = 0; } }
  for (int v: e[u]) { dfs(v,dep+1); }
  ancs.pop_back(); }

void dfs2(int u, int dep) {
  st[u].modify(1,max_dep,dep,1, st[u].R);
  for (int v: e[u]) { dfs2(v, dep+1); st[u].merge(1,max_dep, st[u].R, st[v].R); }
  for (int i: pid[u]) { qs[i].ans = st[u].query(1,max_dep, dep+qs[i].k, st[u].R); } }

void preInit() { } void init() {
  n = sc.n(); q = sc.n();
  repi (i,2,n) e[sc.n()].push_back(i); 
  rep (i,q) { qs[i].u=sc.n(); qs[i].k=sc.n(); qid[qs[i].u].push_back(i); }
} void solve() {
  dfs(1,1); rep (i,q) pid[qs[i].p].push_back(i); 
  dfs2(1,1); rep (i,q) printf("%d ", qs[i].ans-1);
}
