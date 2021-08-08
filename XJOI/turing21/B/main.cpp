#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 8005;
int a[N], n;

void preInit() { } 
void init() 
{
  n = sc.n();
  for (int i = 0; i < n; i++)
    a[i] = sc.n();
  Temps::dissociate(a, a + n, a);
} 

struct STree {
  struct Node {
    int a = 0, b = 0;
    bool flip = false;
    void push_up(const Node &l, const Node &r) { a = l.a + r.a; b = l.b + r.b; }
    void push_flip() { flip ^= 1; std::swap(a, b); }
    void push_down(Node &l, Node &r) { if (flip) { l.push_flip(); r.push_flip(); flip = false; } }
  } p[N * 4];

  void clear() { 
    memset(p, 0, sizeof(p)); }
  void modify(int u, int l, int r, int pos, int type) {
    if (r - l == 1) { (type ? p[u].b : p[u].a)++; return; }
    p[u].push_down(p[u + u], p[u + u + 1]); 
    int mid = (l + r) / 2;
    if (pos < mid) { modify(u + u, l, mid, pos, type); }
    else { modify(u + u + 1, mid, r, pos, type); }
    p[u].push_up(p[u + u], p[u + u + 1]); }
  void flip(int u, int l, int r, int fl, int fr) {
    if (fl <= l && r <= fr) { p[u].push_flip(); return; }
    p[u].push_down(p[u + u], p[u + u + 1]); 
    int mid = (l + r) / 2;
    if (fl < mid) { flip(u + u, l, mid, fl, fr); }
    if (fr > mid) { flip(u + u + 1, mid, r, fl, fr); }
    p[u].push_up(p[u + u], p[u + u + 1]); }
  Node query(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) { return p[u]; }
    p[u].push_down(p[u + u], p[u + u + 1]); 
    int mid = (l + r) / 2;
    if (qr <= mid) return query(u + u, l, mid, ql, qr);
    if (ql >= mid) return query(u + u + 1, mid, r, ql, qr);
    Node al = query(u + u, l, mid, ql, qr);
    Node ar = query(u + u + 1, mid, r, ql, qr);
    Node res; res.push_up(al, ar);
    return res; }
} T;

int suf_id[N];
int solve(int a[], int n)
{
  T.clear();

  struct bar_t { int l, r, cnt; };
  bar_t stack[N];
  auto stack_top = stack;
  bool valid[N];
  int have_edge_cnt = 0;
  for (int i = 0; i < n; i++) 
  {
    *stack_top++ = (bar_t){a[i], a[i], 1};
    while (stack_top - stack >= 2 && stack_top[-1].r > stack_top[-2].l) {
      checkMin(stack_top[-2].l, stack_top[-1].l);
      checkMax(stack_top[-2].r, stack_top[-1].r);
      have_edge_cnt -= (stack_top[-2].cnt > 1);
      have_edge_cnt -= (stack_top[-1].cnt > 1);
      stack_top[-2].cnt += stack_top[-1].cnt;
      have_edge_cnt += (stack_top[-2].cnt > 1);
      stack_top--; }
    valid[i] = have_edge_cnt <= 1;
  }

  const int gl = 0, gr = ::n;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    T.flip(1, gl, gr, gl, a[i]); 
    auto pre = T.query(1, gl, gr, gl, a[i]);
    int pre_sum = pre.a + pre.b;
    T.modify(1, gl, gr, a[i], pre_sum % 2);
    see(i, valid[i], T.p[1].b);
    ans += valid[i] && T.p[1].b == 0; }
  return ans;
}

void solve() 
{
  logArray(a, a + n);
  a[n] = 0x3f3f3f3f;
  int ans = 0;
  for (int i = 0; i < n; i++) 
  {
    ans += solve(a + i, n - i);
    see(ans);
  }
  printf("%d\n", ans);
}
