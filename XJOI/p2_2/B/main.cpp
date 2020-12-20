#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 200005;
constexpr int M = 205;
constexpr int MOD = 998244353;

int a[N], n,m,q;

int calc(int a[], int n, int last) {
  static int next[N][M];
  rep (i,m) next[n][i] = n+1;
  repb (i,n-1,0) {
    memcpy(next[i], next[i+1], sizeof(next[i]));
    next[i][a[i]] = i+1; }
  static int ans[N];
  memset(ans, 0, sizeof(ans));
  rep (i,n) ans[i+1] = a[i]==last;
  repb (i,n,0) { rep (j,m) (ans[i] += ans[ next[i][j] ]) %= MOD; }
  return ans[0];
}

int qs[N];

void preInit() { } void init() { 
  n=sc.n(); m=sc.n(); q=sc.n();
  rep (i,n) a[i] = sc.n()-1;
} void solve() {
  while (q--) {
    int b=sc.n()-1, c=sc.n()-1, d=sc.n()-1;
    int qs_top = 0;
    qs[qs_top++] = c;
    repi (i,b+1,n-1) qs[qs_top++] = a[i];
    rep (i,b) qs[qs_top++] = a[i];
    printf("%d\n", calc(qs, n, d));
  }
}
