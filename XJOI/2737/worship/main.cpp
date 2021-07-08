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

  void __modify(int u, int l, int r, int pos, int delta) {
    if (r - l == 1) { p[u].sum += delta; }
    int mid = l + (r - l) / 2;
    if (pos < mid) __modify(u + u, l, mid, pos, delta);
    else __modify(u + u + 1, mid, r, pos, delta);
    p[u] = Node(p[u + u], p[u + u + 1]); }
  void modify(int pos, int delta) { __modify(root, l, r, pos, delta); }

  int __query(int u, int l, int r, long long thr) {
    if (r - l == 1) { return l; }
    int mid = l + (r - l) / 2;
    if (p[u + u].sum < thr) return __query(u + u, mid, r, thr - p[u + u].sum); 
    else return __query(u + u, l, mid, thr); }
  int query(long long thr) { return __query(root, l, r, thr); }
} T(0, N);

int n, m;
int a[N], b[N], c[N], d[N];

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

std::vector<int> x2a[N], x2b[N];

void solve() 
{

}
