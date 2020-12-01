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

const int N = 100005;
const int M = 25;
const int C = 26;
char a[N], b[M];
int n, m, q;

void preInit()
{

}

int next[N][C];
void init()
{
  scanf("%s", a); scanf("%s", b);
  n = strlen(a); m = strlen(b);
  rep (i,C) next[n][i] = n+1;
  repb (i,n-1,0) {
    memcpy(next[i], next[i+1], sizeof(next[i]));
    next[i][a[i]-'a'] = i; }
}

int dp[M][M];

void solve()
{
  int q; scanf("%d", &q);
  while (q--) {
    int l,r; scanf("%d%d", &l, &r); l--;
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = l;
    repa (i,m) rep (j,m+1) {
      dp[i][j] = dp[i-1][j];
      if (j && dp[i-1][j-1] != 0x3f3f3f3f && next[dp[i-1][j-1]][b[i-1]-'a'] < r) {
        checkMin(dp[i][j], next[dp[i-1][j-1]][b[i-1]-'a'] + 1); } }
    int ans = 0;
    repa (i,m) if (dp[m][i] != 0x3f3f3f3f) { ans = i; }
    printf("%d\n", r-l+m-ans-ans);
  }
}
