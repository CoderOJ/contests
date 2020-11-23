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

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

using namespace Polys;
const int N = 100005;
int a[N], b[N], n, m;

void
preInit()
{}

Poly A, B;

void
init()
{
  n = sc.n();
  m = sc.n();
  A.resize(n + n);
  B.resize(n);
  rep(i, n) A[n + n - i - 1] = A[n - i - 1] = a[i] = sc.n();
  rep(i, n) B[i] = b[i] = sc.n();
}

void
solve()
{
  int min_other = std::numeric_limits<int>::max();
  repi(c, -m - 3, m + 3)
  {
    int attempt = 0;
    rep(i, n)
    {
      attempt += (a[i] + c) * (a[i] + c);
      attempt += (b[i] - 2 * c) * b[i];
    }
    checkMin(min_other, attempt);
  }
  // rep (i,n) A[i] += min_c;
  A *= B;
  int max_sub = 0;
  repi(i, n - 1, 2 * n - 2) checkMax(max_sub, static_cast<int>(A[i]));
  see(min_other, 2 * max_sub);
  printf("%d\n", min_other - 2 * max_sub);
}
