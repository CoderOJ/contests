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
#include <ext/rope>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

using __gnu_cxx::rope;

void
preInit()
{}

struct Fans
{
  int val, ord;
  Fans(int val = 0, int ord = 0)
    : val(val)
    , ord(ord)
  {}
};

const int N = 100005;
Fans a[N];
int n;

void
init()
{
  n = sc.n();
  rep(i, n)
  {
    a[i].val = sc.n();
    a[i].ord = sc.n();
  }
}

void
solve()
{
  std::sort(a, a + n, [](Fans a, Fans b) { return a.val > b.val; });
  std::vector<int> ans;
  rep(i, n)
  {
    if (a[i].ord > i) {
      puts("impossible");
      return;
    }
    checkMin(a[i].ord, i - a[i].ord);
    ans.insert(ans.begin() + a[i].ord, a[i].val);
  }
  rep(i, n) printf("%d ", ans.at(i));
}
