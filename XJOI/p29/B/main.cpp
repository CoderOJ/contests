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

#define int long long

constexpr int N = 1000005;
int a[N], pre[N], n;
bool valid_pos[N];

struct STree {
  struct Node {
    Node *l=nullptr, *r=nullptr;
    int max = std::numeric_limits<int>::min();
    inline void push_up() {
      max = std::numeric_limits<int>::min();
      if (l) { checkMax(max, l->max); }
      if (r) { checkMax(max, r->max); } }
    inline void push_assign(int val) {
      checkMax(max, val); }
  };

  Node *R = nullptr;
  int l, r;
  void init(int l, int r) { this->l = l; this->r = r; }
  void __modify(int p, int l, int r, int val, Node *&u) {
    if (u == nullptr) u = new Node();
    if (l == r) { u->push_assign(val); return; }
    int mid = l + (r-l) / 2;
    if (p <= mid) { __modify(p, l, mid, val, u->l); }
    else { __modify(p, mid+1, r, val, u->r); } 
    u->push_up(); }
  void modify(int p, int val) { 
    __modify(p, l, r, val, R); }
  int __query(int sl, int sr, int l, int r, Node *u) {
    if (u == nullptr) { return std::numeric_limits<int>::min(); }
    if (sl <= l && r <= sr) { return u->max; }
    int mid = (l + r) / 2, res = std::numeric_limits<int>::min();
    if (sl <= mid) { checkMax(res, __query(sl, sr, l,mid, u->l)); }
    if (sr > mid ) { checkMax(res, __query(sl, sr, mid+1,r, u->r)); }
    return res; }
  int query(int sl, int sr) { 
    return __query(sl,sr,l,r,R); }
} St;

void preInit() { } void init() {
  St.init(-1e15, 1e15);
  n = sc.n(); rep (i,n) a[i] = sc.n();
  rep (i,n) pre[i+1] = pre[i] + a[i];
  rep (i,n) { valid_pos[i] = true;
    if (i && a[i] >= a[i-1]) { valid_pos[i] = false; }
    if (i<n-1 && a[i] >= a[i+1]) { valid_pos[i] = false; } }
} void solve() {
  St.modify(St.l, 0);
  rep (i,n) if (valid_pos[i]) {
    int cur = pre[i] - a[i];
    see(i, cur);
    St.modify(pre[i] + 2*a[i], a[i] + St.query(St.l, cur-1)); }
  printf("%lld\n", pre[n] - St.query(St.l, St.r) * 2);
}
