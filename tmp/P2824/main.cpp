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
int a[N], n, m, q;

struct STree {
public:
  static constexpr int root = 1;
  void init(int l, int r) noexcept { g_l = l; g_r = r; __init(l, r); }
  void assign(int l, int r, int val) noexcept { if (r >= l) { __assign(l, r, g_l, g_r, val); } }
  int query(int l, int r) noexcept { if (l > r) { return 0; } return __query(l, r, g_l, g_r); }

protected:
  struct Node {
    int sum=0, assign=-1, len=1;
    void setLength(int len) { this->len = len; }
    void pushAssign(int val) noexcept {
      sum = len * val; assign = val; }
    void pushUp(const Node& l, const Node& r) noexcept {
      sum = l.sum + r.sum; }
    void pushDown(Node& l, Node& r) noexcept {
      if (assign != -1) {
        l.pushAssign(assign); r.pushAssign(assign); assign = -1; } }
  } p[N * 4];

  int g_l, g_r;
  void __init(int l, int r, int u = root) noexcept {
    p[u].setLength(r - l + 1);
    if (l == r) { return; }
    int mid = (l + r) / 2;
    __init(l, mid, u+u); __init(mid+1, r, u+u+1); }
  void __assign(int sl, int sr, int l, int r, int val, int u = root) noexcept {
    if (sl <= l && r <= sr) { p[u].pushAssign(val); return; }
    p[u].pushDown(p[u+u], p[u+u+1]); 
    int mid = (l + r) / 2;
    if (sl <= mid) { __assign(sl,sr, l,mid, val, u+u); }
    if (sr > mid) { __assign(sl,sr, mid+1,r, val, u+u+1); } 
    p[u].pushUp(p[u+u], p[u+u+1]); }
  int __query(int sl, int sr, int l, int r, int u = root) noexcept {
    if (sl <= l && r <= sr) { return p[u].sum; }
    p[u].pushDown(p[u+u], p[u+u+1]); 
    int mid = (l + r) / 2, res = 0;
    if (sl <= mid) { res += __query(sl,sr, l,mid, u+u); }
    if (sr > mid) { res += __query(sl,sr, mid+1,r, u+u+1); }
    return res; }
} st;

struct Action { int l, r, type; } ops[N];

bool jury(int thr) { // to check if (ans <= thr)
  rep (i, n) { st.assign(i, i, a[i] > thr); }
  rep (i,m) {
    int l = ops[i].l, r = ops[i].r;
    int n1 = st.query(l, r), n0 = r-l+1 - n1;
    if (ops[i].type == 0) { st.assign(l, l+n0-1, 0); st.assign(r-n1+1, r, 1); }
    else { st.assign(l, l+n1-1, 1); st.assign(r-n0+1, r, 0); } }
  return st.query(q, q) == 0;
}

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n) a[i] = sc.n();
  rep (i,m) { ops[i].type = sc.n(); ops[i].l = sc.n() - 1; ops[i].r = sc.n() - 1; }
  q = sc.n() - 1;
} void solve() {
  st.init(0, n-1);
  int l = 1, r = n;
  while (l < r) {
    int mid = (l + r) / 2;
    if (jury(mid)) { r = mid; }
    else { l = mid + 1; } }
  printf("%d\n", l);
}
