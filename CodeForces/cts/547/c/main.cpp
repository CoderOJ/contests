#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/range.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

#define in :
constexpr int N = 200005;
constexpr int M = 500005;
int a[N], cnt[M], min_fac[M], mu[M], n, m;
std::vector<int> facs[N];
bool is_on[N];

long long now_pairs;

void euler() {
  static bool isprime[M];
  std::vector<int> primes;
  memset(isprime, true, sizeof(isprime));
  mu[1] = 1; isprime[1] = false;
  for (int i in range(2, M)) {
    if (isprime[i]) { primes.push_back(i); mu[i] = -1; min_fac[i]=i; }
    for (int j in primes) {
      if (i * j >= M) { break; }
      isprime[i * j] = false; min_fac[i * j] = j;
      if (i % j) { mu[i * j] = -mu[i]; }
      else { mu[i * j] = 0; break; } } }
}

std::vector<int> getFactors(int x) {
  std::vector<int> res{1};
  while (x > 1) {
    int pos_fac = min_fac[x], cnt = 0;
    while (min_fac[x] == pos_fac) { x /= pos_fac; cnt++; }
    std::size_t sz = res.size(); res.reserve(sz * (cnt+1));
    int pos_mul = pos_fac;
    for ([[maybe_unused]] int i in range(cnt)) {
      for (int j in range(sz)) {
        res.push_back(res[j] * pos_mul); }
      pos_mul *= pos_fac; } }
  return res;
}

int count(int id) {
  int res = 0;
  for (int u in facs[id]) {
    res += mu[u] * cnt[u]; }
  return res; }

void update(int id, int del) {
  for (int u in facs[id]) {
    cnt[u] += del; } }

void preInit() { euler(); } void init() {
  n = sc.n(); m = sc.n();
  for (int i in range(n)) { a[i] = sc.n(); facs[i] = getFactors(a[i]); }
} void solve() {
  for ([[maybe_unused]] auto _ in range(m)) {
    int pos = sc.n() - 1;
    if (is_on[pos] == false) {
      is_on[pos] = true;
      now_pairs += count(pos); 
      update(pos, 1); }
    else {
      is_on[pos] = false;
      update(pos, -1); 
      now_pairs -= count(pos);  } 
    printf("%lld\n", now_pairs); }
}
