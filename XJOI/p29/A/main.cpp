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

constexpr int MOD = 1000000007;
constexpr int N = 1005;
typedef Temps::Intm<Temps::ConstModuler<MOD>> Int;
int cnt[N * 2], n;
Int nCr[N][N], nCrp[N][N];

inline Int getInter(int n, int l, int r) {
  Int res = nCrp[n][r];
  if (l > 0) { res -= nCrp[n][l-1]; }
  return res; }
Int count(int a, int b, int k) {
  Int ans = 0;
  rep (i,a+1) ans += getInter(b,i-k,i+k) * nCr[a][i];
  return ans; }

void preInit() { 
  nCr[0][0] = 1;
  repa (i,N-1) {
    nCr[i][0] = 1;
    repa (j,i) { nCr[i][j] = nCr[i-1][j-1] + nCr[i-1][j]; } }
  memcpy(nCrp, nCr, sizeof(nCr));
  rep (i,N) repa (j,N-1) nCrp[i][j] += nCrp[i][j-1];
} void init() {
  n = sc.n(); rep (i,n) cnt[sc.n()]++;
} void solve() {
  int pre = 0;
  Int ans = 0;
  repa (i,2*n) {
    int pos = cnt[i], suf = n - pos - pre;
    rep (j,pos) { ans += nCr[pos][j+1] * count(pre,suf,j); } 
    pre += pos; }
  printf("%d\n", static_cast<int>(ans));
}
