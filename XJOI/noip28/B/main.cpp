#include "/home/jack/code/creats/gpl.h"
#define ENABLE_LL
#define MULTIPLE_TEST_CASES_WITH_T

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
int vis[N], cnt[N], n, m, p;
std::vector<int> e[N];
int sz[N];

void
preInit()
{}

void
init()
{
  memset(vis, 0, sizeof(vis));
  memset(cnt, 0, sizeof(cnt));
  memset(sz, 0, sizeof(sz));
  rep(i, N) e[i].clear();
  n = sc.n();
  m = sc.n();
  p = sc.n();
  rep(i, m)
  {
    int x = sc.n(), y = sc.n();
    e[y].push_back(x);
    cnt[x]++;
  }
}

int
power(int a, int b)
{
  int r = 1;
  for (; b; b >>= 1) {
    if (b & 1)
      (r *= a) %= p;
    (a *= a) %= p;
  }
  return r;
}

int
inv(int a)
{
  return power(a, p - 2);
}

int ans;
void
dfs(int u)
{
  if (vis[u]) {
    ans = 0;
    return;
  }
  vis[u] = sz[u] = 1;
  for (int v : e[u]) {
    dfs(v);
    sz[u] += sz[v];
  }
  (ans *= inv(sz[u])) %= p;
}

void
solve()
{
  ans = 1;
  repa(i, n)(ans *= i) %= p;
  repa(i, n) if (!cnt[i]) dfs(i);
  repa(i, n) if (!vis[i])
  {
    puts("0");
    return;
  }
  printf("%lld\n", ans);
}
