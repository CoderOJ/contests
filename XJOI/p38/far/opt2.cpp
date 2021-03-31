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
int F[N][N], DF[N][N], G[N][N];
int binom[N][N], pow2_bk[N][N];
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
  for (int k=1;k<n;++k) for (int b=1;b<n;++b) { pow2_bk[b][k] = power( power(2,k)+p-1, b); }
} void solve() {
  F[1][1] = 1;
  for (int a=2;a<=n;++a) for (int b=1;b<a;++b) {
    int *const pF = F[a-b], *const p2=pow2_bk[b];
    for (int k=1;k<a;++k) { F[a][b] = (F[a][b] + 1ll * pF[k] * p2[k]) % p; }
    F[a][b] = 1ll * F[a][b] * binom[a][b] % p * power(2, b*(b-1)/2) % p; }
  for (int a=2;a<=n;++a) for (int b=1;b<a;++b) {
    int *const pF=F[a-b], *const pDF=DF[a-b], *const p2=pow2_bk[b];
    for (int k=1;k<a;++k) { DF[a][b] = (DF[a][b] + 1ll * (pF[k] + pDF[k]) * p2[k]) % p; }
    DF[a][b] = 1ll * DF[a][b] * binom[a][b] % p * power(2, b*(b-1)/2) % p; }
  for (int a=2;a<=n;++a) for (int b=1;b<a;++b) {
    int *const pF=F[a-b], *const pDF=DF[a-b], *const pG=G[a-b], *const p2=pow2_bk[b];
    for (int k=1;k<a;++k) { 
      G[a][b] = (G[a][b] + (pG[k] + 1ll * (pF[k]+pDF[k]) * b) % p * p2[k]) % p; }
    G[a][b] = 1ll * G[a][b] * binom[a][b] % p * power(2, b*(b-1)/2) % p; }
  int ans = 0;
  for (int b=1;b<n;++b) { ans = (ans + G[n][b]) % p; }
  ans = (1ll * ans * power(n*(n-1)%p, p-2)) % p;
  printf("%d\n", ans);
}
