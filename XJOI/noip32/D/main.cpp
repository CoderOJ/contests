#pragma GCC optimize(2, 3, "Ofast")

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
// #define int long long

/** My code begins here **/

void
preInit()
{}

#define double long double
const int N = 10005;
int a[N], n, m, k, t, full_cnt, full;

void
init()
{
  n = sc.n();
  m = sc.n();
  k = sc.n();
  t = !sc.n();
  rep(i, n) full += a[i] = sc.n();
  full_cnt = (k / full) * n;
  k %= full;
}

inline void
inc(int& a)
{
  a++;
  a = a >= n ? a - n : a;
}

void
solve()
{
  int pos = 0;
  int rem = 0;
  rep(i, m)
  {
    int cur = k;
    double ans = full_cnt;
    while (1) {
      int cur_have = a[pos] - rem;
      if (cur >= cur_have) {
        cur -= cur_have;
        ans += static_cast<double>(cur_have) / a[pos];
        inc(pos);
        rem = 0;
      } else {
        ans += static_cast<double>(cur) / a[pos];
        rem += cur;
        break;
      }
    }
    if (t && rem) {
      rem = 0;
      inc(pos);
    }
    printf("%.2Lf ",ans);
  }
}
