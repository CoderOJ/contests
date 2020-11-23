#include "/home/jack/code/creats/gpl.h"

#define ENABLE_LL

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

const int N = 100005;
struct Obj
{
  int cost, val;
  Obj(int cost = 0, int val = 0)
    : cost(cost)
    , val(val)
  {}
  bool operator<(const Obj& B) const
  {
    return cost == B.cost ? val > B.val : cost > B.cost;
  }
};

int n, m;
Obj a[N];

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
    a[i].cost = sc.nl();
    a[i].val = sc.nl();
  }
  std::sort(a, a + n);
}

void solve()
{
  while (m--) {
    int c = sc.nl();
    int ans = 0;
    rep (i,n) {
      if (c >= a[i].cost) {
        c -= a[i].cost;
        ans += a[i].val;
      }
    }
    printf("%lld\n", ans);
  }
}
