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
using namespace Polys;

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

const int N = 100005;
int n, m;
int cnt[N];

void
preInit()
{}

void
init()
{
  n = sc.n();
  m = sc.n();
  rep(i, n)
  {
    int u = sc.n();
    cnt[u]++;
  }
}

void
solve()
{
  Pre::Inv.require(m+5);
  Poly A(m + 1);
  repa(i, m)
  {
    if (cnt[i] == 0)
      continue;
    for (int j = 1; j * i <= m; j++) {
      A[j * i] -= Int(cnt[i]) * Pre::Inv.inv[j];
    }
  }
  A = A.exp();
  A = A.inv();
  repa (i,m) printf("%u\n", static_cast<unsigned>(A[i]));
}
