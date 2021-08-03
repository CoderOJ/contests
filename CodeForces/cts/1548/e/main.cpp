#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
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


template<typename T>
struct FTree {
  size_t n;
  std::vector<T> a; 

  FTree() {}
  FTree (size_t n) : n(n + 1), a(n + 2) {}
  void init (int _n) {
    n = _n + 1;
    a.resize (n + 1); }
  void add (size_t x, T v) { ++x;
    for (; x <= n; x += x & -x) a[x] += v; }
  T sum (size_t x) { ++x;
    x = std::min (x, n); T ret = 0;
    for (; x; x -= (x & -x)) ret += a[x];
    return ret; } };

struct node_t {
  int a, b, t;
  bool operator < (const node_t &n) const {
    return a < n.a || (a == n.a && t < n.t); } };

std::vector<int> calc(std::vector<int> a) {
  size_t n = a.size();
  std::vector<int> b (n, -1), c (n, -1);
  std::vector<size_t> stk (n); size_t tp = 0;
  for (size_t i = 0; i < n; ++i) {
    int mx = -1;
    while (tp && a[stk[tp - 1]] > a[i]) {
      mx = std::max (mx, a[stk[tp - 1]]);
      mx = std::max (mx, b[stk[tp - 1]]);
      --tp; }
    if (tp) b[i] = mx;
    else b[i] = 1e9;
    stk[tp++] = i; }
  tp = 0;
  for (size_t i = n - 1; i < n; --i) {
    int mx = -1;
    while (tp && a[stk[tp - 1]] >= a[i]) {
      mx = std::max (mx, a[stk[tp - 1]]);
      mx = std::max (mx, c[stk[tp - 1]]);
      --tp; }
    if (tp) c[i] = mx;
    else c[i] = 1e9;
    stk[tp++] = i; }
  for (size_t i = 0; i < n; ++i) 
    checkMin(b[i], c[i]);
  return b; };

std::vector<int> a, b;
size_t n, m;
int x;

void preInit() {  } 
void init()
{
  n = (size_t)sc.n(); m = (size_t)sc.n(); x = sc.n();
  a.resize(n); b.resize(m);
  for (size_t i = 0; i < n; ++i) a[i] = std::min(sc.n(), x);
  for (size_t i = 0; i < m; ++i) b[i] = std::min(sc.n(), x);
}

void solve()
{
  std::vector<int> c = calc (a), d = calc (b);
  std::vector<node_t> vec;
  for (size_t i = 0; i < n; ++i) if (c[i] > a[i]) vec.push_back ({a[i], c[i], 0 });
  for (size_t i = 0; i < m; ++i) if (d[i] > b[i]) vec.push_back ({x - d[i], x - b[i], 1 });
  std::sort (vec.begin(), vec.end() );
  long long ans = 0; FTree<int> st (200005);
  for (auto &p : vec) 
    if (p.t == 0) { ans += st.sum ((size_t)p.b - 1) - st.sum ((size_t)p.a - 1); }
    else { st.add ((size_t)p.b, 1); }
  std::cout << ans << std::endl; 
}
