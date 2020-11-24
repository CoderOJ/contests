#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"
/** My code begins here **/

#define int long long
using namespace Polys;
const int N = 100005;

namespace Math {
int
power(int a, int b)
{
  int r = 1;
  for (; b; b >>= 1) {
    if (b & 1)
      (r *= a) %= MOD;
    (a *= a) %= MOD;
  }
  return r;
}
int
inv(int a)
{
  return power(a, MOD - 2);
}
} /* Math */

int a[N], n, k;

void
preInit()
{}

void
init()
{
  n = sc.n();
  k = sc.n() - 1;
  rep(i, n) a[i] = sc.n();
}

int c[N];

void
solve()
{
  c[0] = 1;
  c[1] = k + 1;
  repi(i, 2, n - 1) { c[i] = c[i - 1] * Math::inv(i) % MOD * (k + i) % MOD; }
  // logArray(c, n);
  Poly A(n), B(n);
  rep(i, n)
  {
    A[i] = a[i] * c[i] % MOD;
    B[i] = c[i];
  }
  A *= B;
  rep(i, n) { printf("%u ", static_cast<unsigned>(A[i])); }
}
