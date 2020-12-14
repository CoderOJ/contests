#include "/home/jack/code/creats/log.h"

namespace Intm {

typedef unsigned int uint32;
typedef unsigned long long uint64;

template<uint32 MOD>
struct Intm
{
  static inline uint32 _mod_red(uint32 a) { return a >= MOD ? a - MOD : a; }
  static inline void _mod_red_set(uint32& a) { a = a >= MOD ? a - MOD : a; }

  uint32 a;
  Intm(uint64 a = 0)
    : a(a % MOD)
  {}
  inline Intm operator+(const Intm B) const { return Intm(_mod_red(a + B.a)); }
  inline Intm& operator+=(const Intm B)
  {
    _mod_red_set(a += B.a);
    return *this;
  }
  inline Intm operator-(const Intm B) const
  {
    return Intm(_mod_red(MOD + a - B.a));
  }
  inline Intm& operator-=(const Intm B)
  {
    _mod_red_set(a += MOD - B.a);
    return *this;
  }
  inline Intm operator*(const Intm B) const
  {
    return Intm(static_cast<uint64>(a) * B.a % MOD);
  }
  inline Intm& operator*=(const Intm B)
  {
    a = static_cast<uint64>(a) * B.a % MOD;
    return *this;
  }
  inline operator uint32() { return a % MOD; }
};
}

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
#include "/home/jack/code/creats/body.h"


/** My code begins here **/

#define int long long

constexpr int MOD = 1000000007;
typedef Intm::Intm<MOD> Int;

std::map<int, Int> getr_mem;
Int getr(int x) {
  if (x == 1) { return Int(1); }
  if (getr_mem.count(x)) { return getr_mem[x]; }
  int ls = (x+1)/2, rs = x-ls;
  Int al = getr(ls), ar = getr(rs);
  return getr_mem[x] = al + Int(ls) + ar - Int(1); 
}

std::map<int, Int> getl_mem;
Int getl(int x) {
  if (x == 1) { return Int(1); }
  if (getl_mem.count(x)) { return getl_mem[x]; }
  int ls = (x+1)/2, rs = x-ls;
  Int al = getl(ls), ar = getl(rs);
  return getl_mem[x] = al + ar + Int(rs) - Int(1);
}

std::map<int, Int> dp;
Int dfs(int x) {
  if (x == 1) { return Int(1); }
  if (dp.count(x)) { return dp[x]; }
  int ls = (x+1) / 2, rs = x - ls;
  Int ans = dfs(ls) + dfs(rs) - Int(1);
  Int lv = getr(ls), rv = getl(rs);
  ans += lv * Int(rs) + rv * Int(ls);
  return dp[x] = ans; 
}

void preInit() { } void init() { } void solve() {
  int n; scanf("%lld", &n);
  printf("%u\n", static_cast<unsigned>( dfs(n) ) );
}
