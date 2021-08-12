#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
// #include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/log.hpp"
// #include "/home/jack/code/creats/range.hpp"
// #include "/home/jack/code/creats/util.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
#define INTM_FAST_64 long long
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr size_t N = 32;
constexpr int MOD = 998244353;
using Int = Temps::Intm<MOD>;
Int inv[N], ipow2[N], binom[N][N];

struct poly_t : public std::array<Int, N>
{
  poly_t integral() const 
  {
    poly_t r;
    r[0] = 0;
    for (size_t i = 0; i + 1 < N; i++)
      r[i + 1] = at(i) * inv[i + 1];
    return r;
  }
  Int eval(Int x) const
  {
    Int ans = 0;
    for (size_t i = N-1; i < N; i--)
      ans = ans * x + at(i);
    return ans;
  }
  Int integral(Int l, Int r)
  {
    auto p = integral();
    return p.eval(r) - p.eval(l);
  }
};

poly_t operator+ (const poly_t &lhs, const poly_t &rhs)
{
  poly_t r;
  for (size_t i = 0; i < N; i++)
    r[i] = lhs[i] + rhs[i];
  return r;
}

poly_t operator* (const poly_t &lhs, const poly_t &rhs)
{
  poly_t r;
  std::fill(r.begin(), r.end(), 0);
  for (size_t i = 0; i < N; i++)
    for (size_t j = 0; i + j < N; j++)
      r[i + j] += lhs[i] * rhs[j];
  return r;
}

poly_t ppow[N];

void
preInit()
{
  inv[0] = inv[1] = 1;
  for (size_t i = 2; i < N; i++)
    inv[i] = inv[MOD % i] * (MOD - MOD / i);
  ipow2[0] = 1;
  for (size_t i = 1; i < N; i++)
    ipow2[i] = ipow2[i - 1] * inv[2];
  for (size_t i = 0; i < N; i++)
  {
    binom[i][0] = 1;
    for (size_t j = 1; j <= i; j++)
      binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
  }
  for (size_t i = 0; i < N; i++)
    for (size_t j = 0; j <= i; j++)
      ppow[i][j] = (j % 2 == 1) ? MOD - binom[i][j] : binom[i][j];
}

int popcount(int x)
{
  return __builtin_popcount(static_cast<unsigned int>(x));
}

int e[N];
int n, m;

std::unordered_map<int, poly_t> dac_mem;
poly_t dac(int u_set)
{
  if (dac_mem.count(u_set))
    return dac_mem.at(u_set);
  
  int mask;
  bool vis[N] = {0};
  std::function<void(int)> dfs = [&](int u)
  {
    if (vis[u]) return;
    vis[u] = true, mask |= (1 << u);
    for (int v = 0; v < n; v++) 
      if ((u_set & e[u]) & (1 << v))
        dfs(v);
  };
  std::vector<int> comps;
  for (int u = 0; u < n; u++)
    if ((u_set & (1 << u)) && !vis[u])
    {
      mask = 0;
      dfs(u);
      comps.push_back(mask);
    }

  poly_t ans;
  std::fill(ans.begin(), ans.end(), 0);
  if (comps.size() == 1)
  {
    ans[0] = ipow2[popcount(u_set)];
    for (int u = 0; u < n; u++) if (u_set & (1 << u))
    {
      int v_set = u_set ^ (1 << u) ^ (u_set & e[u]);
      int k = popcount(u_set & e[u]);
      poly_t cur = (dac(v_set) * ppow[k]).integral();
      cur[0] -= cur.eval(inv[2]);
      ans = ans + cur;
    }
  }
  else
  {
    ans[0] = 1;
    for (int v_mask : comps)
      ans = ans * dac(v_mask);
  }
  dac_mem.insert({u_set, ans});
  return ans;
}

void
init()
{
  n = sc.n(), m = sc.n();
  for (int i = 0; i < m; i++)
  {
    int u = sc.n() - 1, v = sc.n() - 1;
    e[u] |= (1 << v), e[v] |= (1 << u);
  }
}

void
solve()
{
  poly_t F = dac((1 << n) - 1);
  Int ans = 2 - F.eval(1) * inv[n + 1];
  std::reverse(F.begin(), F.begin() + n + 1);
  ans -= F.integral(1, 2);
  std::cout << ans << std::endl;
}
