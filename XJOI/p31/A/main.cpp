#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 1000000007;
using Int = Temps::Intm<Temps::ConstModuler<MOD>>;
constexpr int N = 305;

Int dp[N][N][N];
char s[N];
int n;

void preInit() { } void init() {
  n = sc.n(); sc.next(s);
} void solve() {
  dp[0][0][0] = 1;
  int pre_l=0, pre_r=0, pre_b=0;
  (s[0] == 'L' ? pre_l : (s[0] == 'R' ? pre_r : pre_b))++;
  for (int i=1;i<n;++i) {
    if (s[i] == 'L' || s[i] == 'B') 
    {
      for (int inv=0;inv<i;inv++) {
        for (int last=0;last<i;last++) {
          const Int& pre = dp[i-1][inv][last];
          if (pre != 0) {
            int pl=pre_l, pr=pre_r, pb=pre_b;
            (s[last]=='L' ? pl : (s[last]=='R' ? pr : pb))--;
            dp[i][inv][last] += Int(pb + pr - inv) * pre;
            if (inv) { dp[i][inv-1][last] += Int(inv) * pre; }
            if (s[last] != 'L') { dp[i][inv][i] += pre; }
          } } }
    }
    else
    {
      for (int inv=0;inv<i;inv++) {
        for (int last=0;last<i;last++) {
          const Int& pre = dp[i-1][inv][last];
          if (pre != 0) {
            int pl=pre_l, pr=pre_r, pb=pre_b;
            (s[last]=='L' ? pl : (s[last]=='R' ? pr : pb))--;
            dp[i][inv + 1][last] += Int(pb + pr - inv) * pre;
            dp[i][inv][last] += Int(inv) * pre;
            if (s[last] != 'L') { dp[i][inv][i] += pre; }
          } } }
    }
    (s[i] == 'L' ? pre_l : (s[i] == 'R' ? pre_r : pre_b))++;
  }
  std::cout << dp[n-1][0][n-1] << std::endl;
}
