#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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

constexpr int N = 500005;

/**
 * We need a Segment Tree that supports:
 * modify:
 *   - interval assignment
 * query:
 *   - interval sum
 *   - leftiest position that is lower than x
 */
struct STree {
  struct Node {
    int front=0, len=1, assign=-1;
    long long sum = 0;
    Node() =default;
    Node(const Node& a, const Node& b) :
      front(a.front),
      len(a.len + b.len),
      sum(a.sum + b.sum) {}
    void push_assign(int val) {
      front = assign = val;
      sum = 1ll * len * val; }
    void push_down(Node& a, Node& b) {
      if (assign != -1) {
        a.push_assign(assign);
        b.push_assign(assign);
        assign = -1; } }
  } *p;
  static constexpr int root = 1;
  int l, r;

  void _init(int l, int r, int u) {
    if (r - l == 1) { return; }
    int mid = (l + r + 1) >> 1;
    _init(l, mid, u+u); _init(mid, r, u+u+1);
    p[u] = Node(p[u+u], p[u+u+1]);  }
  STree(int l, int r) : p(new Node[(r-l) * 4]), l(l), r(r) { _init(l,r,root); }

  void _assign(int ml, int mr, int val, int l, int r, int u) {
    if (ml <= l && r <= mr) { p[u].push_assign(val); return; }
    p[u].push_down(p[u+u], p[u+u+1]);
    int mid = (l + r + 1) >> 1;
    if (ml < mid) { _assign(ml, mr, val, l, mid, u+u); }
    if (mr > mid) { _assign(ml, mr, val, mid, r, u+u+1); }
    p[u] = Node(p[u+u], p[u+u+1]); }
  void assign(int ml, int mr, int val) {
    slog("STree::assign [%d,%d) := %d", ml,mr,val);
    _assign(ml, mr, val, l, r, root); }

  Node _query(int ql, int qr, int l, int r, int u) {
    if (ql <= l && r <= qr) { return p[u]; }
    p[u].push_down(p[u+u], p[u+u+1]);
    int mid = (l + r + 1) >> 1;
    if (ql >= mid) { return _query(ql, qr, mid, r, u+u+1); }
    if (qr <= mid) { return _query(ql, qr, l, mid, u+u); }
    return Node(_query(ql, qr, l, mid, u+u), _query(ql, qr, mid, r, u+u+1)); }
  Node query(int ql, int qr) { return _query(ql, qr, l, r, root); }

  int _lower_bound(int val, int l, int r, int u) {
    if (r - l == 1) { return l; }
    p[u].push_down(p[u+u], p[u+u+1]);
    int mid = (l + r + 1) >> 1; 
    if (p[u+u+1].front >= val) { return _lower_bound(val, mid, r, u+u+1); }
    else { return _lower_bound(val, l, mid, u+u); } }
  int lower_bound(int val) { return _lower_bound(val, l, r, root); }

  ~STree() { delete[] p; }
};

struct Fans { int b, c; };
Temps::Vector<Fans> fans[N];
int n, na, nb, nc;
int least_b[N], least_c[N];

void preInit() { } void init() {
  n = sc.n(); na = sc.n(); nb = sc.n(); nc = sc.n();
  for (int i=0; i<n; ++i) { int a=sc.n(), b=sc.n(), c=sc.n(); fans[a].push_back({b,c}); }
} void solve() {
  int lb=1, lc=1;
  for (int pa = na; pa >= 1; pa--) {
    for (const auto& fan: fans[pa]) {
      checkMax(lb, fan.b + 1); checkMax(lc, fan.c + 1); }
    least_b[pa] = lb; least_c[pa] = lc; }

  long long ans = 0;
  STree T(-1, nb+1);
  for (int pa = 1; pa <= na; pa++) {
    lb = least_b[pa]; lc = least_c[pa];
    ans += 1ll * (nb-lb+1) * (nc-lc+1);
    int r_pos = T.lower_bound(lc);
    if (r_pos >= lb) {
      ans -= T.query(lb, r_pos+1).sum - 1ll * (r_pos-lb+1) * (lc-1); }

    for (const auto& fan: fans[pa]) {
      int l_pos = T.lower_bound(fan.c);
      if (l_pos <= fan.b) {
        T.assign(l_pos+1, fan.b+1, fan.c); } } }

  printf("%lld\n", ans);
}
