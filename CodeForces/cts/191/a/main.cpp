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

constexpr int N = 500005;
char name[N][15];
int len[N];
int n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i=0; i<n; i++) {
    sc.next(name[i]); len[i] = (int)std::strlen(name[i]); }
} 

int dp[128][128];
void solve() 
{
  memset(dp, 0xcf, sizeof(dp));
  for (int i=0; i<128; i++) dp[i][i] = 0;
  for (int i=0; i<n; i++) {
    int l = (int)name[i][0], r = (int)name[i][len[i] - 1];
    for (int j=0; j<128; j++) 
      checkMax(dp[j][r], dp[j][l] + len[i]); }
  int ans = 0;
  for (int i=0; i<128; i++) checkMax(ans, dp[i][i]);
  printf("%d\n", ans);
}
