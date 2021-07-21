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


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 100005;

struct bit_t {
  int a[2] = {0,0};
  bit_t() =default;
  bit_t(int x, int y) : a{x,y} {} 
  bit_t(char x) : a{x!='1', x!='0'} {}
};

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
};

std::ostream& operator<< (std::ostream& out, dp_t x) {
  out << std::make_pair(std::make_pair(x.a[0][0], x.a[0][1]), std::make_pair(x.a[1][0], x.a[1][1])); 
  return out; }
std::ostream& operator<< (std::ostream& out, bit_t x) {
  out << std::make_pair(x.a[0], x.a[1]);
  return out; }

int trans_rule[2][2][2];
bit_t trans(bit_t a0, bit_t a1, bit_t a2) {
  bit_t res;
  for (int i0=0; i0<2; i0++)
    for (int i1=0; i1<2; i1++)
      for (int i2=0; i2<2; i2++)
        res.a[trans_rule[i0][i1][i2]] |= a0.a[i0] && a1.a[i1] && a2.a[i2];
  return res; }

char s[N];
bit_t a[N];
int n;

void preInit() {  } 
void init() 
{
  for (int i0=0; i0<2; i0++)
    for (int i1=0; i1<2; i1++)
      for (int i2=0; i2<2; i2++)
        trans_rule[i2][i1][i0] = sc.nextChar() - '0';
  sc.next(s); n = static_cast<int>(std::strlen(s));
  for (int i=0; i<n; i++) a[i] = bit_t(s[i]);
} 

dp_t dp[N];

void solve() 
{
  int ln = n / 2;
  dp[0] = dp_t(trans(a[0], a[1], {1,0}), trans(a[0], a[1], {0,1}));
  for (int i=1; i<ln; i++) {
    dp_t cur0;
    {
      bit_t a0 = dp[i - 1].apply(a[i * 2]);
      cur0 = dp_t(trans(a0, a[i*2 + 1], {1,0}), trans(a0, a[i*2 + 1], {0,1}));
    }
    dp_t cur1(dp[i - 1].apply(trans(a[i * 2], a[i*2 + 1], {1,0})),
              dp[i - 1].apply(trans(a[i * 2], a[i*2 + 1], {0,1})));
    dp[i] = cur0 || cur1;
  }
  // see(dp[0]);
  bit_t res = dp[ln - 1].apply(a[n - 1]);
  printf("%d\n", static_cast<int>(res.a[1]) > 0);
}
