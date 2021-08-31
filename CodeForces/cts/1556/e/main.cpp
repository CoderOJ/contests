#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define int long long

/** My code begins here **/

constexpr int N = 100005;
int a[N], n, q;
int pre[N];

void preInit() {  } 
void init() 
{
  n = sc.n(); q = sc.n();
  for (int i = 1; i <= n; i++) a[i] = sc.n();
  for (int i = 1; i <= n; i++) a[i] = sc.n() - a[i];
  for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
} 

constexpr int B = 20;
struct st_table
{
  int min[N][B], max[N][B];
  int log[N];
  void init(int *a, int n)
  {
    log[1] = 0;
    for (int i = 2; i < N; i++) log[i] = log[i >> 1] + 1;
    for (int i = 1; i <= n; i++) min[i][0] = max[i][0] = a[i];
    for (int b = 0; b + 1 < B; b++)
      for (int i = 1; i <= n - (1<<b); i++)
      {
        min[i][b + 1] = std::min(min[i][b], min[i + (1<<b)][b]);
        max[i][b + 1] = std::max(max[i][b], max[i + (1<<b)][b]);
      }
  }
  int query_min(int l, int r)
  {
    int len = r - l + 1, b = log[len];
    return std::min(min[l][b], min[r - (1 << b) + 1][b]);
  }
  int query_max(int l, int r)
  {
    int len = r - l + 1, b = log[len];
    return std::max(max[l][b], max[r - (1 << b) + 1][b]);
  }
} st;

void solve() 
{
  st.init(pre, n);
  for (int i = 0; i < q; i++)
  {
    int l = sc.n(), r = sc.n();
    // see(l, r, pre[l - 1], pre[r]);
    if (pre[l - 1] != pre[r]) { puts("-1"); continue; }
    int imin = st.query_min(l, r), imax = st.query_max(l, r);
    if (imin < pre[r]) { puts("-1"); continue; }
    printf("%lld\n", imax - pre[r]);
  }
}
