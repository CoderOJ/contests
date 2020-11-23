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

const int N = 200005;
int valid[N], cnt[N];
int n, q;

void
preInit()
{}

void
init()
{
  n = sc.n();
  q = sc.n();
  repa(i, n)
  {
    valid[i] = 1;
    cnt[i] = sc.n();
  }
}

struct Num
{
  int sum, cnt;
  Num(int sum = 0, int cnt = 0)
    : sum(sum)
    , cnt(cnt)
  {}
  void add(int k) { cnt += k; }
  void move() { sum += cnt; }
};

Num pre[N], suf[N];

void
solve()
{
  while (q--) {
    int ty = sc.n();
    if (ty == 1) {
      int x = sc.n(), k = sc.n();
      cnt[x] += k;
    } else if (ty == 2) {
      int x = sc.n(), k = sc.n();
      cnt[x] -= k;
    } else if (ty == 3) {
      int l = sc.n(), r = sc.n();
      repi(i, l, r) valid[i] = 1;
    } else {
      int l = sc.n(), r = sc.n();
      repi(i, l, r) valid[i] = 0;
    }

    pre[0] = Num(0, 0);
    repa(i, n)
    {
      pre[i] = pre[i - 1];
      pre[i].move();
      pre[i].add(cnt[i]);
    }
    suf[n + 1] = Num(0, 0);
    repb(i, n, 1)
    {
      suf[i] = suf[i + 1];
      suf[i].move();
      suf[i].add(cnt[i]);
    }

    int best = 0x3f3f3f3f3f3f3f3f, best_id = -1;
    repa(i, n) if (valid[i])
    {
      if (checkMin(best, pre[i].sum + suf[i].sum)) {
        best_id = i;
      }
    }
    printf("%lld\n", best_id);
  }
}
