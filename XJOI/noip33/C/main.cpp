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

const int MOD = 998244353;
const int N = 2000055;
const int B = 22;
int a[N], n, m;
unsigned sd;

int
rd()
{
  return (sd ^= sd << 13, sd ^= sd >> 17, sd ^= sd << 5) % n + 1;
}

void
preInit()
{}

void
init()
{
  n = sc.n(); m = sc.n(); sd = sc.nl();
  rep(i, n) a[i] = sc.n();
}

std::vector<int> e[N];
void
getL()
{
  typedef std::pair<int, int> Item;
  std::vector<Item> st;
  st.push_back(Item(0x3f3f3f3f, -1));
  rep(i, n)
  {
    while (st.back().first < a[i]) {
      e[i].push_back(st.back().second);
      st.pop_back();
    }
    st.push_back(Item(a[i], i));
  }
  while (st.back().first < 0x3f3f3f3f) {
    e[n].push_back(st.back().second);
    st.pop_back();
  }
}

int dfn[N], ll[B][N], dfn_cnt;
int depth[N], lg[N];
inline int
min(int a, int b)
{
  return a < b ? a : b;
}
void
dfs1(int u, int f)
{
  depth[u] = depth[f] + 1;
  dfn[u] = dfn_cnt;
  ll[0][dfn_cnt] = depth[u];
  dfn_cnt++;
  for (int v : e[u]) {
    dfs1(v, u);
    ll[0][dfn_cnt] = depth[u];
    dfn_cnt++;
  }
}

void
init_lca()
{
  dfn_cnt = 0;
  dfs1(n, n);
  rep(i, B - 1) rep(j, dfn_cnt - (1 << i))
  {
    ll[i+1][j] = min(ll[i][j], ll[i][j + (1 << i)]);
  }
  lg[1] = 0;
  repi(i, 2, N - 1) lg[i] = lg[i / 2] + 1;
}

inline int
lca(int u, int v)
{
  int l = dfn[v], r = dfn[u];
  int s = lg[r - l + 1];
  return min(ll[s][l], ll[s][r - (1 << s) + 1]);
}

void
solve()
{
  getL();
  init_lca();
  long long ans = 0;
  repa(i, m)
  {
    int l = rd()-1, r = rd()-1;
    if (l > r) std::swap(l,r);
    int bottom = depth[l];
    int top = lca(l, r + 1);
    (ans += 1ll * i * (bottom - top)) %= MOD;
  }
  printf("%lld\n", ans);
}
