#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
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

constexpr int N = 405;
int f[N][N][N], g[N][N][N];
int binom[N][N], pow2_kb[N][N];
int n, p;

int power(int a, int b) {
  int r = 1;
  for (;b;b>>=1) {
    if (b & 1) { r = 1ll * r * a % p; }
    a = 1ll * a * a % p; }
  return r; }

void preInit() { } void init() {
  n = sc.n(); p = sc.n();
  binom[0][0] = 1;
  for (int i=1;i<=n;++i) { binom[i][0] = 1; for (int j=1;j<=i;++j) { binom[i][j] = (binom[i-1][j-1] + binom[i-1][j]) % p; } }
  for (int k=1;k<n;++k) for (int b=1;b<n;++b) { pow2_kb[k][b] = power( power(2,k)+p-1, b); }
} void solve() {
  f[0][1][1] = 1;
  for (int d=1;d<n;++d) {
    for (int a=d+1;a<=n;++a) {
      for (int b=1;b<a;++b) {
        for (int k=1;k<a;++k) {
          f[d][a][b] = (f[d][a][b] + 1ll * f[d-1][a-b][k] * pow2_kb[k][b]) % p; }
        f[d][a][b] = 1ll * f[d][a][b] * binom[a][b] % p * power(2, b*(b-1)/2) % p; } } }
  for (int d=1;d<n;++d) {
    for (int a=d+1;a<=n;++a) {
      for (int b=1;b<a;++b) {
        for (int k=1;k<a;++k) {
          g[d][a][b] = (g[d][a][b] + (g[d-1][a-b][k] + 1ll * f[d-1][a-b][k] * d * b) % p * pow2_kb[k][b]) % p; }
        g[d][a][b] = 1ll * g[d][a][b] * binom[a][b] % p * power(2, b*(b-1)/2) % p; } } }
  int ans = 0;
  for (int d=1;d<n;++d) for (int b=1;b<n;++b) { ans = (ans + g[d][n][b]) % p; }
  ans = (1ll * ans * power(n*(n-1)%p, p-2)) % p;
  printf("%d\n", ans);
}
