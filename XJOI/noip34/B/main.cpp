#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

typedef unsigned long long u64;
const u64 MOD = 1000000000000000000;
const int N = 505;
char a[N];
int n;

void preInit() { } 
void init()
{ scanf("%s", a); n = strlen(a); }

u64 dp[N][N];

void solve()
{
  dp[0][0] = 1;
  repa (i,n) rep (j,i+1) {
    dp[i][j] = dp[i-1][j];
    if (j && a[i-1] == a[j-1]) {
      (dp[i][j] += dp[i-1][j-1]) %= MOD; } }
  u64 ans = 0;
  rep (i,n+1) { (ans += dp[n][i]) %= MOD; }
  char output[20];
  sprintf(output, "%llu", ans);
  for (int i=0,len=strlen(output); i+len<18; ++i) { putchar('0'); }
  puts(output);
}
