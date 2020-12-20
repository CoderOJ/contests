#include "/home/jack/code/creats/loop.h"
#include <bits/stdc++.h>

constexpr int N = 2e5 + 7;
constexpr int C = 202;
constexpr int MOD = 998244353;
int n, m, q, f[N], las[N];
int mata[N + C][C], dya[N + C][C];
int matb[N + C][C], dyb[N + C][C];

int Fa(int t, int x, int y) {
  if (x == m + 1) return mata[t][y];
  else return (MOD - mata[dya[t][x]][y]) % MOD; }

int Fb(int t, int x, int y) {
  if (y == m + 1) return matb[t][x];
  else return matb[dyb[t][y]][x]; }

int main() {
  scanf("%d%d%d", &n, &m, &q);
  if (q == 0)
    return 0;
  repi(i, 1, n) scanf("%d", &f[i]);
  repi(i, 1, m) mata[i + n + 1][i] = MOD - 1, matb[i + n + 1][i] = 1, dya[n + 1][i] = dyb[0][i] = i + n + 1;
  mata[n + 1][m + 1] = matb[0][m + 1] = 1;
  repb (i, n, 1) {
    repi(j, 1, m) {
      if (f[i] != j) dya[i][j] = dya[i + 1][j];
      else dya[i][j] = i + 1; }
    repi(j, 1, m + 1) mata[i][j] = (2ll * Fa(i + 1, m + 1, j) % MOD + Fa(i + 1, f[i], j)) % MOD; }
  repi(i, 1, n) {
    repi(j, 1, m) {
      if (f[i] != j) dyb[i][j] = dyb[i - 1][j];
      else dyb[i][j] = i - 1; }
    repi(j, 1, m + 1) matb[i][j] = (2ll * Fb(i - 1, j, m + 1) % MOD + MOD - Fb(i - 1, j, f[i])) % MOD; }
  while (q--) {
    int a, b, c; scanf("%d%d%d", &a, &b, &c);
    int res = 0;
    repi(i, 1, m + 1) (res += 1ll * (2ll * Fa(a + 1, m + 1, i) % MOD + Fa(a + 1, b, i)) % MOD * Fb(a - 1, i, c) % MOD) %= MOD;
    printf("%d\n", res); }
  return 0;
}
