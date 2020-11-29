#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define int long long

/** My code begins here **/

void
preInit()
{}

void
init()
{}

int MOD;

int
power(int a, int b)
{
  b %= (MOD - 1);
  int r = 1;
  for (; b; b >>= 1) {
    if (b & 1)
      (r *= a) %= MOD;
    (a *= a) %= MOD;
  }
  return r;
}

inline int
inv(int a)
{
  return power(a, MOD - 2);
}

const int N = 2005;
int fac[N], iv[N], ia[N], p2[N];
int ans[N][N];

void
solve()
{
  int T = sc.n();
  MOD = sc.n();
  fac[0] = iv[0] = ia[0] = p2[0] = 1;
  repa (i,N-1) {
    fac[i] = fac[i-1]*i % MOD;
    iv[i] = inv(fac[i]);
    ia[i] = inv(i);
    p2[i] = p2[i-1] * 2 % MOD;
  }
  {
    ans[1][0] = 1;
    ans[1][1] = 2;
    for (int i = 2; i < N; ++i) {
      for (int j = 0; j < i; ++j) {
        ans[i][j] = ans[i-1][j] * p2[j] % MOD * i % MOD * ia[i-j] % MOD;
      }
      for (int j = 0; j <= i; ++j) {
        int a = j, b = i-j;
        int cho = a * b;
        int com = fac[i] * iv[a] % MOD * iv[b] % MOD;
        (ans[i][i] += power(2,cho) * com) %= MOD;
      }
    }
  }
  while (T--) {
    int n = sc.n();
    int res = 0;
    rep (i,n+1) (res += ans[n][i]) %= MOD;
    printf("%lld\n", res);
  }
}
