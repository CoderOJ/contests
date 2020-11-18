#define ENABLE_LL
#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

const int MOD = 998244353;
const int N = 100005;
const int B = 31;

int a[N];
int n, k;

namespace Math
  {
    int fac[N], ifac[N];

    void init()
      {
        fac[0] = 1;
        for (int i = 1; i < N; ++ i)
          fac[i] = fac[i-1] * i % MOD;
        ifac[0] = ifac[1] = 1;
        for (int i = 2; i < N; ++ i)
          ifac[i] = (MOD-MOD/i) * ifac[MOD%i] % MOD;
        for (int i = 1; i < N; ++ i)
          (ifac[i] *= ifac[i-1]) %= MOD;
      }

    int binom(int n, int r)
      {
        if (r < 0 || r > n)
          return 0;
        see(n, r);
        see(fac[n], ifac[r], ifac[n-r]);
        return fac[n] * ifac[r] % MOD * ifac[n-r] % MOD;
      }
  }

void preInit() { }
void init()
{
  n = sc.n(); k = sc.n();
  rep (i,n) a[i] = sc.n();
  Math::init();
}

int wc[B];

int calc(int x)
  {
    int res = 0;
    for (int i = 1; i <= x; i += 2)
      (res += Math::binom(x, i) * Math::binom(n-x, k-i)) %= MOD;
    return res;
  }

void solve()
{
  rep (i,n) repb (j,B-1,0) if ((a[i] >> j) & 1) wc[j]++;
  see(wc[0], wc[1], wc[2]);
  int ans = 0;
  repb (j,B-1,0) (ans += (1ll<<j) * calc(wc[j])) %= MOD;
  printf("%lld\n", ans);
}
