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

#define long long long
constexpr int N = 100005;
constexpr int B = 62;
long a[N], opt, n;

struct LinearBasis {
  long a[B+1];
  LinearBasis() { memset(a, -1, sizeof(a)); }
  void insert(long x) {
    repb (i,B,0) if ((x>>i) & 1) {
      if (a[i] == -1) { a[i] = x; break; }
      else { x ^= a[i]; } } }
  long queryMin(long x) {
    repb (i,B,0) if (a[i] != -1) {
      checkMin(x, x ^ a[i]); }
    return x; }
  long queryMax(long x) {
    repb (i,B,0) if (a[i] != -1) {
      checkMax(x, x ^ a[i]); }
    return x; }
  void buildMin() {
    repb (i,B,0) if (a[i] != -1) {
      long u=a[i]; a[i]=-1; a[i]=queryMin(u); } }
} Lb;

void preInit() { } void init() {
  opt = sc.n(); n = sc.n();
  rep (i,n) a[i] = sc.nl();
} void solve() {
  if (opt == 0) 
  {
    rep (i,n) Lb.insert(a[i]);
    Lb.buildMin();
    long ans = 0; repb (i,B,0) if (Lb.a[i] != -1) ans += Lb.a[i];

  } 
  else 
  {
    std::sort(a, a+n, [](int a, int b) { return a>b; });
    long ans = 0;
    rep (i,n) {
      ans += Lb.queryMax(a[i]);
      Lb.insert(a[i]); }
    printf("%lld\n", ans);
  }
}
