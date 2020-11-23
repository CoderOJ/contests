#include "/home/jack/code/creats/gpl.h"

#define ENABLE_LL

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

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
Obj p[N];

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
  p[0] = Obj(0, 0);
  rep(i, n)
  {
    p[i + 1].cost = p[i].cost + a[i].cost;
    p[i + 1].val = p[i].val + a[i].val;
  }
}

int
attempt(int& c)
{
  if (c < a[n - 1].cost) {
    c = 0;
    return 0;
  }
  int lst = 0, rst = n - 1;
  while (lst < rst) {
    int mid = (lst + rst) / 2;
    if (a[mid].cost <= c) {
      rst = mid;
    } else {
      lst = mid + 1;
    }
  }
  int st = lst;
  int led = st, red = n - 1;
  while (led < red) {
    int mid = (led + red + 1) / 2;
    if (p[mid + 1].cost - p[st].cost <= c) {
      led = mid;
    } else {
      red = mid - 1;
    }
  }
  int ed = led;
  c -= p[ed + 1].cost - p[st].cost;
  if (ed == n - 1) {
    c = 0;
  }
  return p[ed + 1].val - p[st].val;
}

void
solve()
{
  while (m--) {
    int c = sc.nl();
    int ans = 0;
    int del = 0;
    while ((del = attempt(c)) != 0) {
      ans += del;
    }
    printf("%lld\n", ans);
  }
}
