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

// #define int long long
#define long long long

constexpr int N = 128;
using Mask = std::bitset<N>;

struct Basis {
  Mask p[N]; long val[N];
  void insert(Mask u, long uval) {
    for (int i=0; i<N; i++) if (u[i]) {
      if (!p[i].any()) { p[i] = u; val[i] = uval; break; }
      else { if (uval > val[i]) { std::swap(u, p[i]); std::swap(uval, val[i]); } u ^= p[i]; } } }
  long query() { return std::accumulate(val, val+N, 0ll); }
} bs;

int n, m;

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
} void solve() {
  for (int i=0; i<m; ++i) {
    long u=sc.n() - 1, v=sc.n() - 1, a=sc.nl(), w=sc.n();
    Mask m(a); m[u + 62] = m[v + 62] = 1;
    bs.insert(m, w);
    printf("%lld\n", bs.query()); }
}
