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


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

void preInit(){}

constexpr int MOD = 1000000007;
using Int = Temps::Intm<MOD>;

std::vector<Int> add, mul;
int n;
Int s;

void init() 
{
  n = sc.n(); s = sc.n(); 
  add.clear(); mul.clear();
  for (int i = 0; i < n; i++)
  {
    char c = sc.nextChar();
    Int d = sc.n();
    if (c == '*') { mul.push_back(d); }
    else { add.push_back(d); }
  }
} 

Int mask[2][1024];

template <int type>
Int dfs(Int, int, int);
template <>
Int dfs<0> (Int cur, int mask_u, int mask_v);
template <>
Int dfs<1> (Int cur, int mask_u, int mask_v);

template <>
Int dfs<0> (Int cur, int mask_u, int mask_v)
{
  if (mask_v == 0)
    return cur + mask[0][mask_u];
  Int res(MOD - 1);
  for (int i = mask_u; i; i = (i - 1) & mask_u)
    checkMin(res, dfs<1>(cur + mask[0][i], mask_v, mask_u ^ i));
  return res;
}

template <>
Int dfs<1> (Int  cur, int mask_u, int mask_v)
{
  if (mask_v == 0)
    return cur * mask[1][mask_u];
  Int res(MOD - 1);
  for (int i = mask_u; i; i = (i - 1) & mask_u)
    checkMin(res, dfs<0>(cur * mask[1][i], mask_v, mask_u ^ i));
  return res;
}

void solve() 
{
  if (mul.size() >= 7)
  {
    mask[0][0] = 0;
    for (size_t i = 0; i < add.size(); i++)
      for (size_t j = 0; j < (1 << i); j++)
        mask[0][j | (1 << i)] = mask[0][j] + add[i];
    mask[1][0] = 1;
    for (size_t i = 0; i < mul.size(); i++)
      for (size_t j = 0; j < (1 << i); j++)
        mask[1][j | (1 << i)] = mask[1][j] * mul[i];
    std::cout << std::min(dfs<0>(s, (1<<add.size())-1, (1<<mul.size())-1), 
                          dfs<1>(s, (1<<mul.size())-1, (1<<add.size())-1)) << std::endl;
  }
  else
  {
    Int ans = MOD - 1;
    for (Int x : mul) s *= x;
    std::sort(mul.begin(), mul.end());
    std::vector<Int> a1{0}, a2{0};
    do
    {
      a1.clear(); a2.clear();
      a1.reserve(100000); a2.reserve(100000);
      a1.push_back(0); a2.push_back(0);
      size_t h = add.size() / 2;
      for (size_t i = 0; i < h; i++)
      {
        size_t a1_size = a1.size();
        Int cur = add[i];
        for (Int t : mul) { cur *= t;
          for (size_t i = 0; i < a1_size; i++) a1.push_back(a1[i] + cur); }
        for (size_t j = 0; j < a1_size; j++) a1[j] += add[i];
      }
      for (size_t i = h; i < add.size(); i++)
      {
        size_t a2_size = a2.size();
        Int cur = add[i];
        for (Int t : mul) { cur *= t;
          for (size_t i = 0; i < a2_size; i++) a2.push_back(a2[i] + cur); }
        for (size_t j = 0; j < a2_size; j++) a2[j] += add[i];
      }
      std::sort(a1.begin(), a1.end());
      for (Int x: a2)
      {
        x += s;
        checkMin(ans, x + a1[0]);
        auto p = std::lower_bound(a1.begin(), a1.end(), MOD - x);
        if (p != a1.end()) checkMin(ans, x + *p);
      }
    } while (std::next_permutation(mul.begin(), mul.end()));
    std::cout << ans << std::endl;
  }
}

