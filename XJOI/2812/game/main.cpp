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
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

#define rep(i,n) for (int i=0; i<n; i++)

constexpr int N = 100005;
constexpr int MOD = 998244353;
using Int = Temps::Intm<MOD>;

struct bit_t {
  int a[2] = {0,0};
  bit_t() =default;
  bit_t(int x, int y) : a{x,y} {} 
  bit_t(int x) : a{x==0, x==1} {}
};

int trans_rule[2][2][2];
bit_t trans(bit_t a0, bit_t a1, bit_t a2) {
  bit_t res;
  rep(i0,2) rep(i1,2) rep(i2,2)
    res.a[trans_rule[i0][i1][i2]] |= a0.a[i0] && a1.a[i1] && a2.a[i2];
  return res; }

struct dp_t {
  int a[2][2] = {{0,0}, {0,0}};
  dp_t() =default;
  dp_t(int x00, int x01, int x10, int x11) : a{{x00,x01}, {x10,x11}} {}
  dp_t(bit_t x0, bit_t x1) : a{{x0.a[0], x0.a[1]}, {x1.a[0], x1.a[1]}} {}

  bit_t apply(const bit_t b) {
    return bit_t{ (a[0][0] && b.a[0]) || (a[1][0] && b.a[1]),
                  (a[0][1] && b.a[0]) || (a[1][1] && b.a[1]) }; }
  dp_t operator|| (const dp_t b) {
    return dp_t(a[0][0] || b.a[0][0], a[0][1] || b.a[0][1],
                a[1][0] || b.a[1][0], a[1][1] || b.a[1][1]); } 
  dp_t next(bit_t a0, bit_t a1) {
    bit_t pre = apply(a0);
    dp_t next0(trans(pre, a1, {1,0}), trans(pre, a1, {0,1}));
    dp_t next1(apply(trans(a0, a1, {1,0})), apply(trans(a0, a1, {0,1})));
    return next0 || next1; }
};

struct dpdp_t {
  Int a[2][2][2][2] = {{{{0,0},{0,0}},{{0,0},{0,0}}},{{{0,0},{0,0}},{{0,0},{0,0}}}};
  dpdp_t() =default;
  Int& operator[](const dp_t t) {
    return a[t.a[0][0]][t.a[0][1]][t.a[1][0]][t.a[1][1]]; }
  dpdp_t operator+ (const dpdp_t b) { dpdp_t r;
    rep (i0,2) rep(i1,2) rep(i2,2) rep(i3,2)
      r.a[i0][i1][i2][i3] = a[i0][i1][i2][i3] + b.a[i0][i1][i2][i3];
    return r; }
  dpdp_t next(bit_t a0, bit_t a1) { dpdp_t r;
    rep (i0,2) rep(i1,2) rep(i2,2) rep(i3,2)
      r[dp_t(i0,i1,i2,i3).next(a0,a1)] += a[i0][i1][i2][i3];
    return r; }
};

std::pair<int,int> a[N];
dpdp_t dp[N];
char s[N];
int n;

void preInit() {  } 
void init() 
{
  for (int i0=0; i0<2; i0++)
    for (int i1=0; i1<2; i1++)
      for (int i2=0; i2<2; i2++)
        trans_rule[i2][i1][i0] = sc.nextChar() - '0';
  sc.next(s); n = static_cast<int>(std::strlen(s));
  for (int i=0; i<n; i++) {
    if (s[i] == '0') a[i] = {0, 1};
    else if (s[i] == '1') a[i] = {1, 2};
    else a[i] = {0, 2}; }
} 

void solve() 
{
  if (n == 1) { printf("%d\n", s[0] == '1' || s[0] == '?'); }
  const int ln = n / 2;
  memset(dp, 0, sizeof(dp));
  for (int i0=a[0].first; i0<a[0].second; i0++)
    for (int i1=a[1].first; i1<a[1].second; i1++)
      dp[0][dp_t(trans(i0,i1,0), trans(i0,i1,1))] += 1;
  for (int i=1; i<ln; i++) {
    for (int i0=a[i*2+0].first; i0<a[i*2+0].second; i0++)
      for (int i1=a[i*2+1].first; i1<a[i*2+1].second; i1++)
        dp[i] = dp[i] + dp[i-1].next(i0, i1); }
  Int ans = 0;
  for (int i=a[n-1].first; i<a[n-1].second; i++)
    rep (i0,2) rep(i1,2) rep(i2,2) rep(i3,2)
      if (dp_t(i0,i1,i2,i3).apply(i).a[1] > 0)
        ans += dp[ln - 1].a[i0][i1][i2][i3];
  printf("%d\n", static_cast<int>(ans));
}
