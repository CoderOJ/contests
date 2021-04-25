#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

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

constexpr int N = 500005;

struct STree {
  struct Node {
    int a=0, b=0;
    bool flip_flag = false; 
    Node() =default;
    Node(const Node &l, const Node &r) : 
      a(std::max(l.a, r.a)), b(std::max(l.b, r.b)) {}
    void flip() { std::swap(a, b); flip_flag = !flip_flag; }
    void push_down(Node &l, Node &r) {
      if (flip_flag) { l.flip(); r.flip(); flip_flag = false; } }
  } p[N * 4];

  void init(int *a, int l, int r, int u) {
    if (r - l == 1) { p[u].a = a[l]; return; }
    int mid = (l + r) / 2;
    init(a, l, mid, u+u); init(a, mid, r, u+u+1); 
    p[u] = Node(p[u+u], p[u+u+1]); }
  void flip(int fl, int fr, int l, int r, int u) {
    if (fl <= l && r <= fr) { p[u].flip(); return; }
    p[u].push_down(p[u+u], p[u+u+1]);
    int mid = (l + r) / 2;
    if (fl < mid) flip(fl, fr, l, mid, u+u);
    if (fr > mid) flip(fl, fr, mid, r, u+u+1);
    p[u] = Node(p[u+u], p[u+u+1]); }
  Node query(int ql, int qr, int l, int r, int u) {
    if (ql <= l && r <= qr) { return p[u]; }
    p[u].push_down(p[u+u], p[u+u+1]);
    int mid = (l + r) / 2;
    if (ql >= mid) { return query(ql, qr, mid, r, u+u+1); }
    if (qr <= mid) { return query(ql, qr, l, mid, u+u); }
    return Node(query(ql, qr, l, mid, u+u), query(ql, qr, mid, r, u+u+1)); }
};

Vector<int> e[N];
int u[N], v[N], w[N], n, m, r1, r2;

std::pair<int, int> get_farthest(int u, int f) {
  std::pair<int, int> res(-1, u);
  for (int v: e[u]) if (v != f) {
    checkMax(res, get_farthest(v, u)); } 
  res.first++;
  return res; }

struct Tree {
  STree st;
  int dep[N], dfnl[N], dfnr[N], dfn_top=0;
  void dfs(int u, int f) {
    dfnl[u] = dfn_top++;
    dep[dfnl[u]] = dep[dfnl[f]] + 1;
    for (int v: e[u]) if (v != f) dfs(v, u);
    dfnr[u] = dfn_top; } 
  void init(int r) {
    dep[0] = -1;
    dfs(r, 0); st.init(dep, 0, n, 1); }
  void flip(int u, int v) {
    if (dep[dfnl[v]] > dep[dfnl[u]]) { u = v; }
    st.flip(dfnl[u], dfnr[u], 0, n, 1); }
  int query() { return st.query(0, n, 0, n, 1).a; }
} T1, T2;

void preInit() { } void init() {
  n = sc.n();
  for (int i=1; i<n; ++i) {
    u[i] = sc.n(), v[i] = sc.n(), w[i] = sc.n();
    e[u[i]].push_back(v[i]), e[v[i]].push_back(u[i]); }
  m = sc.n();
} void solve() {
  r1 = get_farthest(1, 0).second; T1.init(r1); 
  r2 = get_farthest(r1, 0).second; T2.init(r2);
  see(r1, r2);
  for (int i=1; i<n; ++i) if (w[i]) { T1.flip(u[i], v[i]); T2.flip(u[i], v[i]); }
  for (int i=0; i<m; ++i) {
    int id = sc.n();
    T1.flip(u[id], v[id]); T2.flip(u[id], v[id]);
    printf("%d\n", std::max(T1.query(), T2.query())); }
}
