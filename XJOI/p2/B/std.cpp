#include "/home/jack/code/creats/log.h"
#include <bits/stdc++.h>

const int N = 1e2;
int MOD, n, k, a[N+5][N+5], b[N+5][N+5], val[N+5][N+5];

inline bool isPrime(int x) {
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) { return false; } }
  return true; }
inline int power(int x, int k) {
  int ans = 1;
  for (; k > 0; k >>= 1, (x *= x) %= MOD) {
    if (k & 1) { (ans *= x) %= MOD; } }
  return ans; }
inline int inver(int x) { return power(x, MOD - 2); }

inline int getG() {
  std::vector<int> fac;
  int x = MOD - 1;
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      fac.push_back(i);
      for (; x % i == 0; x /= i); } }
  if (x > 1) { fac.push_back(x); }
  for (int g = 2;; g++) {
    bool flg = true;
    for (auto x : fac) {
      if (power(g, (MOD - 1) / x) == 1) {
        flg = false; break; } }
    if (flg) { return g; } } }

inline int det() {
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    int p = i;
    for (int j = i; j <= n; j++) {
      if (b[j][i] > b[p][i]) { p = j; } }
    if (p != i) {
      std::swap(b[i], b[p]);
      ans = MOD - ans; }
    if (b[i][i] == 0) { return 0; }
    for (int j = i + 1; j <= n; j++) {
      int t = b[j][i] * inver(b[i][i]) % MOD;
      for (int k = i; k <= n; k++) {
        b[j][k] = (b[j][k] - b[i][k] * t % MOD + MOD) % MOD; } }
    (ans *= b[i][i]) %= MOD; }
  return ans; }

inline int solve(int w) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      b[i][j] = a[i][j] == -1 ? 0 : val[i][j] * power(w, a[i][j]) % MOD; } }
  return det(); }

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
      scanf("%d", &a[i][j]); }
  for (int i = 10000 / k;; i++) {
    if (isPrime(i * k + 1)) {
      MOD = i * k + 1; break; } }
  see(MOD);
  std::mt19937 rng(0);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      val[i][j] = std::uniform_int_distribution<int>(1, MOD - 1)(rng); } }
  int G = getG(), w = power(G, (MOD - 1) / k), wk = 1, ans = 0;
  see(G, w);
  for (int i = 0; i < k; i++) {
    ans += solve(wk); (wk *= w) %= MOD; }
  printf("%s\n", ans % MOD ? "Yes" : "No");
  return 0;
}
