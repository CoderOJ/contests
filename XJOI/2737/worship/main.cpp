#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
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
    long long sum = 0;
    Node() =default;
    Node(const Node a, const Node b) : sum(a.sum + b.sum) {}
  } p[N * 4 + 20];

  static constexpr int root = 1;
  int l, r;
  STree (int l, int r) : l(l), r(r) {}

  void __modify(int u, int l, int r, int pos, long long delta) {
    if (r - l == 1) { p[u].sum += delta; return; }
    int mid = l + (r - l) / 2;
    if (pos < mid) __modify(u + u, l, mid, pos, delta);
    else __modify(u + u + 1, mid, r, pos, delta);
    p[u] = Node(p[u + u], p[u + u + 1]); }
  void modify(int pos, long long delta) { __modify(root, l, r, pos, delta); }

  long long __query(int u, int l, int r, int ql, int qr) {
    see(u, l, r, ql, qr);
    if (ql <= l && r <= qr) return p[u].sum; 
    int mid = l + (r - l) / 2;
    if (ql >= mid) return __query(u + u + 1, mid, r, ql, qr);
    else if (qr <= mid) return __query(u + u, l, mid, ql, qr);
    return __query(u + u, l, mid, ql, qr) + __query(u + u + 1, mid, r, ql, qr); }
  long long query(int l, int r) { 
    if (l >= r) { return 0; }
    return __query(root, this->l, this->r, l, r); }

  int __query_index(int u, int l, int r, long long thr) {
    see(u, l, r, thr);
    if (r - l == 1) { return l; }
    int mid = l + (r - l) / 2;
    see(p[u + u].sum, p[u + u + 1].sum);
    if (p[u + u].sum < thr) return __query_index(u + u + 1, mid, r, thr - p[u + u].sum); 
    else return __query_index(u + u, l, mid, thr); }
  int query_index(long long thr) { return __query_index(root, l, r, thr); }
} T(0, N);

int n, m;
int a[N], b[N];
long long c[N], d[N];

void preInit() 
{ 
  
} 

void init() 
{
  n = sc.n(); m = sc.n();
  for (int i=0; i<n; ++i) a[i] = sc.n() - 1;
  for (int i=0; i<m; ++i) b[i] = sc.n() - 1;
  for (int i=0; i<n; ++i) c[i] = sc.n();
  for (int i=0; i<m; ++i) d[i] = sc.n();
} 

std::vector<int> x2b[N];

void solve() 
{
  for (int i=0; i<m; ++i)
    if (b[i] >= 0)
      x2b[b[i]].push_back(i);

  long long ans = 0;
  for (int i=n-1; i>=0; i--) {
    for (int j: x2b[i])
      T.modify(j, d[j]);
    long long bsum;
    while (c[i] && (bsum = T.query(0, a[i] + 1))) {
      see(i, c[i], bsum);
      int dec_pos = T.query_index(bsum);
      long long dec_val = std::min(c[i], T.query(dec_pos, dec_pos + 1));
      see(dec_pos, dec_val);
      // see(T.query(0, dec_pos));
      ans += dec_val, c[i] -= dec_val, T.modify(dec_pos, -dec_val); } }

  std::cout << ans << std::endl;
}
