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
#define INTM_FAST_64 long long
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
using Int = Temps::Intm<MOD>;
struct poly_t : public std::vector<Int>
{
  size_t n = 0;
  poly_t() =default;
  poly_t(size_t x, size_t y) 
  {
    while (x >= (1 << n) || y >= (1 << n)) n++;
    resize(1 << n);
    if (x) at(x) += 1;
    if (y) at(y) += 1;
  }
  poly_t(std::initializer_list<Int> a) : std::vector<Int>(a)
  {
    while (a.size() > (1 << n)) n++;
    std::vector<Int>::resize(1 << n);
  }

  void resize(size_t l)
  {
    n = 0;
    while (l > (1 << n)) n++;
    std::vector<Int>::resize(1 << n);
  }

  void dft()
  {
    static std::unique_ptr<size_t[]> rev;
    static size_t rev_n = 128;
    if (rev_n != n)
    {
      rev_n = n;
      rev.reset(new size_t[size()]);
      rev[0] = 0;
      for (size_t i = 1; i < size(); i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (n - 1));
    }

    static std::unique_ptr<Int[]> w;
    static size_t w_n = 0;
    if (w_n < n)
    {
      w_n = n;
      w.reset(new Int[size()]);
      for (size_t i = 1; i < size(); i <<= 1)
      {
        w[i] = 1;
        Int pw = Int(3).pow((MOD - 1) / (i * 2));
        for (size_t j = 1; j < i; j++)
          w[i + j] = pw * w[i + j - 1];
      }
    }

    for (size_t i = 0; i < size(); i++)
      if (rev[i] < i)
        std::swap(at(i), at(rev[i]));
    for (size_t l = 1; l < size(); l <<= 1)
      for (size_t j = 0; j < size(); j += l * 2)
        for (size_t k = 0; k < l; k++)
        {
          Int x = at(j + k), y = at(j + l + k) * w[l + k];
          at(j + k) = x + y;
          at(j + l + k) = x - y;
        }
  }

  void idft()
  {
    std::reverse(begin() + 1, end());
    dft();
    Int inv_l = Int(size()).inv();
    for (Int& x : *this)
      x *= inv_l;
  }

  void trim()
  {
    while (n && std::all_of(begin() + (1<<(n-1)), end(), [](Int a){ return a == 0; }))
      n--, resize(1 << n);
  }
};

poly_t operator* (poly_t lhs,  poly_t rhs)
{
  size_t vs = lhs.size() + rhs.size() - 1;
  lhs.resize(vs), rhs.resize(vs);
  lhs.dft(), rhs.dft();
  for (size_t i = 0; i < lhs.size(); i++)
    lhs[i] *= rhs[i];
  lhs.idft();
  lhs.trim();
  return lhs;
}

poly_t operator+ (const poly_t &lhs, const poly_t &rhs)
{
  if (lhs.n < rhs.n) return rhs + lhs;
  poly_t res = lhs;
  for (size_t i = 0; i < rhs.size(); i++)
    res[i] += rhs[i];
  return res;
}

void padd_shift(poly_t &a, const poly_t &b, size_t sh)
{
  if (sh == 0) return;
  if (a.size() < b.size() + sh)
    a.resize(b.size() + sh);
  for (size_t i = 0; i < b.size(); i++)
    a[i + sh] += b[i];
}

constexpr int N = 100005;
std::vector<int> eo[N];
size_t n, m;

void preInit() {  } 
void init() 
{
  n = (size_t)sc.n(); m = (size_t)sc.n();
  for (size_t i = 0; i < m; i++)
  {
    int u = sc.n(), v = sc.n();
    eo[u].push_back(v); eo[v].push_back(u);
  }
} 

std::vector<int> e[N];
std::pair<int,int> eu[N];

int dep[N], ofa[N], fa[N];
void dfs(int u, int f)
{
  ofa[u] = f;
  dep[u] = dep[f] + 1;
  bool skip = true;
  for (int v: eo[u]) if (v != f || !(skip && !(skip=false)))
  {
    if (dep[v] == 0) dfs(v, u);
    else if (dep[v] < dep[u])
    {
      int p = u;
      int len = dep[u] - dep[v] + 1;
      while (p != v)
      {
        fa[p] = v;
        e[v].push_back(p);
        eu[p] = {dep[p] - dep[v], len - (dep[p] - dep[v])};
        p = ofa[p];
      }
    }
  }
  if (fa[u] == 0)
  {
    fa[u] = f;
    e[f].push_back(u);
    eu[u] = {1, 0};
  }
}

bool vis[N];
int size[N];
void get_size(int u)
{
  size[u] = 1;
  for (int v: e[u]) if (!vis[v])
    get_size(v), size[u] += size[v];
}
int tot_size, best_val, best_id;
void get_root(int u)
{
  int cur_val = tot_size - size[u];
  for (int v: e[u]) if (!vis[v])
    get_root(v), checkMax(cur_val, size[v]);
  if (checkMin(best_val, cur_val))
    best_id = u;
}

int u2o[N];
poly_t u2o_p[N];
poly_t dac(int u)
{
  int ou = u;
  get_size(u), tot_size = size[u];
  best_val = std::numeric_limits<int>::max();
  get_root(u); u = best_id; vis[u] = true; u2o[u] = ou;
  
  poly_t ans{0};
  if (ou != u) ans = dac(ou);

  poly_t to_o{1};
  int p = u;
  while (p != ou)
  {
    to_o = to_o * poly_t((size_t)eu[p].first, (size_t)eu[p].second);
    p = fa[p];
    to_o = to_o * u2o_p[p];
    p = u2o[p];
  }

  poly_t sp{1};
  for (int v: e[u]) if (!vis[v])
  {
    auto pv = dac(v);
    padd_shift(sp, pv, (size_t)eu[v].first);
    padd_shift(sp, pv, (size_t)eu[v].second);
  }
  ans = ans + to_o * sp;
  u2o_p[u] = std::move(to_o);
  return ans;
}

void solve() 
{
  dfs(1, 0);
  auto ans = dac(1);
  if (ans.size() < n) ans.resize(n);
  for (size_t i = 1; i < n; i++)
    printf("%d\n", static_cast<int>(ans[i]));
}
