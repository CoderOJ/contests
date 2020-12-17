#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

constexpr int N = 105;

namespace Math {

int power(int a, int b, int MOD) {
  int r = 1;
  for (;b;b>>=1) {
    if (b & 1) r = 1ll * r * a % MOD;
    a = 1ll * a * a % MOD; }
  return r; }
int inv(int a, int MOD) {
  return power(a, MOD-2, MOD); }
std::vector<int> getFactors (int u) {
  std::vector<int> res;
  for (int i=2; i*i<=u; ++i) {
    if (u % i == 0) { 
      res.push_back(i);
      while (u%i==0) { u/=i; } } }
  if (u > 1) { res.push_back(u); }
  return res; }
int getG(int u) {
  auto factors = getFactors(u-1);
  for (int attempt=2;; ++attempt) {
    bool valid = true;
    for (int fac : factors) {
      if (power(attempt, (u-1)/fac, u) == 1) {
        valid = false; break; } }
    if (valid) { return attempt; } } }
bool isPrime(int u) {
  for (int i=2; i*i<=u; ++i) {
    if (u % i == 0) { return false; } }
  return true; }

} /* Math */

struct Matrix {
protected:
  int a[N][N], n;

public:
  Matrix (int n=0) : n(n) {}
  int* operator [] (const int id) { return a[id]; }
  int det(int MOD) {
    int ans = 1;
    for (int i=0; i<n; ++i) {
      int max_id = i;
      for (int j=i; j<n; ++j) { if (a[j][i] > a[max_id][i]) { max_id = j; } }
      if (max_id != i) { ans = (MOD - ans) % MOD; }
      for (int j=0; j<n; ++j) { std::swap(a[i][j], a[max_id][j]); }
      if (a[i][i] == 0) { return 0; }
      for (int j=i+1; j<n; ++j) {
        int delta = 1ll * a[j][i] * Math::inv(a[i][i], MOD) % MOD;
        for (int k=i; k<n; ++k) {
          a[j][k] = (a[j][k] + MOD - 1ll * a[i][k] * delta % MOD) % MOD; } }
      ans = 1ll * ans * a[i][i] % MOD; }
    return ans; }
};

int a[N][N], val[N][N], n, k;

int getAns(int w, int MOD) {
  Matrix b(n);
  rep (i,n) rep (j,n) {
    if (a[i][j] == -1) { b[i][j] = 0; }
    else { b[i][j] = 1ll * val[i][j] * Math::power(w, a[i][j], MOD) % MOD; } }
  return b.det(MOD); }

int getMod() {
  for (int attempt = 10000/k;; attempt++) {
    if (Math::isPrime(attempt * k + 1)) {
      return attempt * k + 1; } } }

void preInit() { } void init() { 
  n = sc.n(); k = sc.n();
  rep (i,n) rep (j,n) { a[i][j] = sc.nextInt(); }
} void solve() {
  int MOD = getMod();
  see(MOD);
  std::mt19937 rand(20050610);
  rep (i,n) rep (j,n) val[i][j] = std::uniform_int_distribution<int>(1, MOD-1)(rand);
  int g = Math::getG(MOD), w = Math::power(g, (MOD-1)/k, MOD), wk=1, ans=0;
  see(g, w);
  for (int i=0; i<k; ++i) {
    ans = (ans + getAns(wk, MOD)) % MOD;
    see(ans, wk);
    wk = 1ll * wk * w % MOD; }
  puts(ans % MOD ? "Yes" : "No");
}
