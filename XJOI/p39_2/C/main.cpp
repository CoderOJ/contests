#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"

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

constexpr int MOD = 998244353;
constexpr int N = 5005;
int stir[N][N];
int a[N], n, m;

void preInit() { 
  stir[0][0] = 1;
  for (int i=1; i<N; ++i) {
    for (int j=1; j<=i; ++j) {
      stir[i][j] = (stir[i-1][j-1] + 1ll * stir[i-1][j] * j) % MOD; } } }

void init() {
  n = sc.n(); m = sc.n();
  for (int i=0; i<n; ++i) { a[i] = sc.n(); }
} 

void solve() {

}
