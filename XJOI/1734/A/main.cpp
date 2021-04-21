#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

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

constexpr int N = 13;
int fac[N], n, q;
int trans[N][N];

int cnt[1 << 12][N];
bool valid() {
  memset(cnt, 0, sizeof(cnt));
  cnt[0][0] = 1;
  for (int i=0; i<(1<<n); ++i) {
    for (int j=0; j<=n; ++j)
      for (int k=0; k<n; ++k)
        if (!(i & (1 << k)))
          cnt[i | (1<<k)][trans[j][k]] += cnt[i][j]; }
  see(cnt[(1<<n)-1][n]);
  return false; }

void preInit() { 
  fac[0] = 1;
  for (int i=1; i<N; ++i)
    fac[i] = fac[i-1] * i;
} void init() {
  n = sc.n(); q = sc.n();
} void solve() {
  for (int i=0; i<n; ++i) 
    trans[n][i] = n;
  for (int i=0; i<n; ++i)
    for (int j=0; j<n; ++j)
      trans[i][j] = n-1;
  int pq = q;
  for (int i=0; i<n; ++i) {
    int pos = fac[n - i - 1], top = 0;
    while (pq >= pos) {
      trans[i][top++] = n;
      pq -= pos; }
    if (trans[i][n-i-1] == n-1 && i != n-1)
      trans[i][n-i-1] = i + 1; }
  valid();
  printf("%d\n", n + 1);
  for (int i=0; i<=n; ++i)
    for (int j=0; j<n; ++j)
      printf("%d%c", trans[i][j] + 1, " \n"[j==n-1]);
  puts("1");
  printf("1 %d\n", n+1);
}
