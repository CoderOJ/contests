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

const int N = 605;
int n, m, p;
int a[N];

void
init()
{
  n = sc.n();
  m = sc.n();
  p = sc.n();
  repa(i, n) a[i] = sc.nl();
}

int ans = 0;
std::vector<int> cand;

int
calc()
{
  int res = 0;
  repi(i, 2, n)
  {
    if (a[i] * cand[i] < m) {
      return 0x3f3f3f3f3f3f3f3f;
    }
    res += abs(a[i] * cand[i] / m - a[i - 1] * cand[i - 1] / m);
  }
  return res;
}

void
dfs(int rem_n, int rem_k)
{
  if (rem_n == 0) {
    checkMin(ans, calc());
    return;
  }
  if (cand.back() != -1) {
    cand.push_back(cand.back());
    dfs(rem_n - 1, rem_k);
    cand.pop_back();
  }
  if (rem_k) {
    repa(i, m)
    {
      cand.push_back(i);
      dfs(rem_n - 1, rem_k - 1);
      cand.pop_back();
    }
  }
}

void
solve()
{
  ans = 0x3f3f3f3f3f3f3f3f;
  cand.push_back(-1);
  dfs(n, p + 1);
  printf("%lld\n", ans);
}
