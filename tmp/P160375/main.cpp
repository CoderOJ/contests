#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

const int N = 1000005;
int n;
int mu[N], fac[N];
bool isPrime[N]; std::vector <int> prime;
void euler() {
  rep (i,N) isPrime[i] = 1; mu[1] = 1; fac[1] = 1;
  repi (i,2,N-1) {
    if (isPrime[i]) { prime.push_back(i); mu[i]=-1; fac[i]=i; }
    for (int j: prime) {
      int u = i*j;
      if (u >= N) { break; }
      isPrime[u]=0; fac[u] = j;
      if (i % j == 0) { mu[u] = 0; break; } 
      else { mu[u] = -mu[i]; } } } }

constexpr int MOD = 998244353;
typedef Intm::Intm<998244353> Int;
Int p[N];

std::vector<int> getFac(int a) {
  std::vector<int> res(1,1);
  while (a > 1) {
    int pos = fac[a], cnt = 0;
    while (fac[a] == pos) { cnt++; a /= fac[a]; }
    int len = res.size();
    int del = pos;
    rep (i,cnt) {
      rep (j,len) res.push_back(res[j] * del); 
      del *= pos; } }
  return res;
}

void preInit() { } void init() {
  euler();
} void solve() {
  int c=sc.n(), n=sc.n();
  p[0] = 1; repa (i,N-1) p[i] = p[i-1] * Int(c);
  Int ans = 0;
  repa (i,n) {
    Int pos = 0;
    auto facs = getFac(i);
    for (int u: facs) {
      see(i, u, mu[i/u], p[u]);
      pos += Int(mu[i/u] + MOD) * p[u]; }
    ans += pos / Int(i); }
  printf("%u\n", static_cast<unsigned>(ans));
}
