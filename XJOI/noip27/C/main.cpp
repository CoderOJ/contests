#include "/home/jack/code/creats/gpl.h"

// #include "/home/jack/code/creats/Scanner.h"
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

#define long long long
const int N = 1000005;
const long MOD = 1000000007;
std::vector<int> e[N];
long w[N];
char opt_str[10];
int n, opt;

void
preInit()
{}

long
op(long a, long b)
{
  if (opt == 0)
    return a ^ b;
  if (opt == 1)
    return a | b;
  return a & b;
}

void
init()
{
  scanf("%d%s", &n, opt_str);
  if (opt_str[0] == 'X') {
    opt = 0;
  } else if (opt_str[0] == 'O') {
    opt = 1;
  } else {
    opt = 2;
  }
  repa(i, n) scanf("%lld", &w[i]);
  repi(i, 2, n)
  {
    int f;
    scanf("%d", &f);
    e[f].push_back(i);
  }
}

namespace solve01 {
long ans = 0;

void
dfs(int u, long cur)
{
  (ans += (cur + w[u]) % MOD * u) %= MOD;
  for (int v : e[u]) {
    long vcur = cur + op(w[u], w[v]);
    dfs(v, vcur);
  }
}
void
main()
{
  dfs(1, 0);
  printf("%lld\n", ans);
}
} // namespace solve01

namespace solve2 {

const int B = 31;
int top[B];
long dp[N];
long ans;

void
dfs(int u)
{
  int _top_bak[B];
  long pans = 0;
  for (int i = 0; i < B; ++i) {
    _top_bak[i] = top[i];
    checkMax(pans,dp[top[i]] + (w[top[i]] & w[u]));
    if ((w[u] >> i) & 1) {
      top[i] = u;
    }
  }
  dp[u] = pans;
  (ans += pans % MOD * u % MOD) %= MOD;
  for (int v: e[u]) dfs(v);
  for (int i = 0; i < B; ++ i)
    top[i] = _top_bak[i];
}
void
main()
{
  memset(top, 0, sizeof(top));
  dfs(1);
  repa (i,n) (ans += w[i] * i) %= MOD;
  printf("%lld\n", ans);
}

} // namespace solve2

void
solve()
{
  if (opt <= 1) {
    solve01::main();
  } else {
    solve2::main();
  }
}
