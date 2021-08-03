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

long long ans = std::numeric_limits<long long>::min();
int n, u, r;

void dfs (int d, bool x, Vector<int> &a, Vector<int> &b, Vector<int> &k, Vector<int> &p) {
  if ( (u - d) % 2 == 0) { long long res = 0;
    for (int i = 0; i < n; i++) { res += static_cast<long long> (a[i]) * static_cast<long long> (k[i]); }
    checkMax (ans, res); }
  if (d == u) return;

  if (x) {
    Vector<int> olda = a;
    for (int i = 0; i < n; i++) { a[i] = olda[p[i]] + r; }
    dfs (d + 1, false, a, b, k, p);
    a = olda; }
  else {
    Vector<int> olda = a;
    for (int i = 0; i < n; i++) { a[i] = olda[p[i]] + r; }
    dfs (d + 1, false, a, b, k, p);
    a = olda;

    for (int i = 0; i < n; i++) { a[i] ^= b[i]; }
    dfs (d + 1, true, a, b, k, p);
    a = olda; } }

void preInit() {  }
void init() { n = sc.nextInt(); u = sc.nextInt(); r = sc.nextInt(); }

void solve() {
  Vector<int> a (n), b (n), k (n), p (n);
  for (auto &x : a) x = sc.nextInt();
  for (auto &x : b) x = sc.nextInt();
  for (auto &x : k) x = sc.nextInt();
  for (auto &x : p) x = sc.nextInt() - 1;
  dfs (0, false, a, b, k, p);
  std::cout << ans << std::endl; }
