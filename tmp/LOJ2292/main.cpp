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

constexpr int N = 55;
int a[N], n, A, B;
int id2val[N];
int f[N][N], dp[N][N][N];

void preInit() { } void init() {
  n = sc.n(); A = sc.n(); B = sc.n();
  for (int i=0; i<n; ++i) id2val[i] = a[i] = sc.n();
  std::sort(id2val, id2val + n);
  for (int i=0; i<n; ++i) a[i] = static_cast<int>(std::lower_bound(id2val, id2val + n, a[i]) - id2val);
} void solve() {
  memset(f, 0x3f, sizeof(f));

  for (int i=n-1; i>=0; i--) {
    memset(dp, 0x3f, sizeof(dp));
    memset(dp[i], 0, sizeof(dp[i]));
    f[i][i] = 0;
    for (int j=i+1; j<=n; ++j) {
      for (int l=0; l<n; ++l) 
        for (int r=l; r<n; ++r) {
          for (int k=i; k<j; ++k)
            checkMin(dp[j][l][r], dp[k][l][r] + f[k][j]);
          checkMin(dp[j][std::min(l, a[j-1])][std::max(r, a[j-1])], dp[j - 1][l][r]); }
      for (int l=0; l<n; ++l)
        for (int r=l; r<n; ++r) 
          checkMin(f[i][j], dp[j][l][r] + A + B * (id2val[r] - id2val[l]) * (id2val[r] - id2val[l])); } }
  printf("%d\n", f[0][n]);
}
