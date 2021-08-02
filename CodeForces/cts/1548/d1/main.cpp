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


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

int cnt[2][2], n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i=0; i<n; i++) {
    int x = sc.n(), y = sc.n();
    cnt[x / 2 % 2][y / 2 % 2]++; }
} 

#define rep(i,n) for (int i=0;i<n;i++)
void solve() 
{
  long long ans = 0;
  rep (ai,2) rep (aj,2)
    rep (bi,2) rep (bj,2)
      rep (ci,2) rep(cj,2)
        if (ai*2+aj < bi*2+bj && bi*2+bj < ci*2+cj)
          if ((((ai^bi) || (aj^bj)) ^
               ((ai^ci) || (aj^cj)) ^
               ((bi^ci) || (bj^cj)))  == 0) {
            ans += 1ll * cnt[ai][aj] * cnt[bi][bj] * cnt[ci][cj]; }
  rep (ai,2) rep (aj,2)
    rep (bi,2) rep (bj,2)
      rep (ci,2) rep(cj,2)
        if (ai*2+aj == bi*2+bj && bi*2+bj < ci*2+cj)
          if ((((ai^bi) || (aj^bj)) ^
               ((ai^ci) || (aj^cj)) ^
               ((bi^ci) || (bj^cj)))  == 0) {
            ans += 1ll * cnt[ai][aj] * (cnt[bi][bj]-1) / 2 * cnt[ci][cj]; }
  rep (ai,2) rep (aj,2)
    rep (bi,2) rep (bj,2)
      rep (ci,2) rep(cj,2)
        if (ai*2+aj < bi*2+bj && bi*2+bj == ci*2+cj)
          if ((((ai^bi) || (aj^bj)) ^
               ((ai^ci) || (aj^cj)) ^
               ((bi^ci) || (bj^cj)))  == 0) {
            ans += 1ll * cnt[ai][aj] * cnt[bi][bj] * (cnt[ci][cj] - 1) / 2; }
  rep (ai,2) rep (aj,2)
    rep (bi,2) rep (bj,2)
      rep (ci,2) rep(cj,2)
        if (ai*2+aj == bi*2+bj && bi*2+bj == ci*2+cj)
          if ((((ai^bi) || (aj^bj)) ^
               ((ai^ci) || (aj^cj)) ^
               ((bi^ci) || (bj^cj)))  == 0) {
            ans += 1ll * cnt[ai][aj] * (cnt[bi][bj]-1) * (cnt[ci][cj]-2) / 6; }
  printf("%lld\n", ans);
}
