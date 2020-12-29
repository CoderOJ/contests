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

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 9;
#define X(a) (a/3)
#define Y(a) (a%3)
inline bool conflict(int a, int b) { return X(a) == X(b) || Y(a) == Y(b); }
int h[N];

bool test(int a, int b) {
  int only = -1;
  rep (i,N) if (!conflict(i,a) && !conflict(i,b)) { only = i; break; }
  int xor_sum = h[only];
  rep (i,N) if (i != a && i != b && i != only) { xor_sum ^= (h[i] - 1); }
  return xor_sum; }

void preInit() { } void init() {
  rep (i,N) h[i] = sc.n();
} void solve() {
  int ans = 0;
  rep (i,N) {
    bool valid = true;
    rep (j,N) if (!conflict(i,j)) { valid &= test(i, j); }
    ans += valid; }
  printf("%d\n", ans);
}
