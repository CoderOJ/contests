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
constexpr int N = 300005;
using Int = Temps::Intm<MOD>;
Int inv[N];

uint64_t hash_cpow[N];
using hash_val_t = uint64_t;
using hash_ord_t = std::pair<size_t, hash_val_t>;
hash_ord_t hash_join(hash_ord_t a, hash_ord_t b)
{
  return hash_ord_t(a.first + b.first,
                    a.second + hash_cpow[a.first] * b.second);
}

void preInit() 
{ 
  hash_cpow[0] = 1;
  hash_cpow[1] = 82061943317773333ull;
  for (int i = 2; i < N; i++)
    hash_cpow[i] = hash_cpow[i - 1] * hash_cpow[1];
  inv[1] = 1;
  for (int i = 2; i < N; i++)
    inv[i] = inv[MOD % i] * (MOD - MOD / i);
} 

std::vector<int> e[N];
int dep[N];
int m;

Int ans = 1;
hash_ord_t dfs(int u)
{
  hash_ord_t res = {0,0}; 
  std::vector<hash_ord_t> sons;
  for (int v: e[u]) 
    sons.push_back(dfs(v));
  std::sort(sons.begin(), sons.end(), std::greater<hash_ord_t>());
  hash_ord_t last = {0,0}; int cnt = 0;
  for (const auto &v_hash : sons) 
  {
    if (v_hash == last) cnt++;
    else { last = v_hash; cnt = 1; }
    res = hash_join(res, v_hash);
    ans *= cnt;
  }
  res = hash_join(res, {1,dep[u]});
  return res;
}

void init() 
{
  m = sc.n();
} 

void solve() 
{
  int u = 2;
  dep[1] = 1;
  for (int i = 0; i < m; i++)
  {
    int opt = sc.n(), f = sc.n();
    if (opt == 0) { e[f].push_back(u); dep[u] = dep[f] + 1; u++; }
    else { ans = 1; dfs(f); std::cout << ans << std::endl; }
    // printf("round %d:\n", i);
    // for (int i = 1; i < u; i++) printf("%lu\n", dfs(i).second);
  }
}
