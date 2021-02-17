#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
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

constexpr int N = 1005;
constexpr int C = 26;
char s[N], t[N];
int dp[N][N], cnt[C], first[N], n;

void preInit() { } void init() {
  sc.next(s); sc.next(t);
  n = std::strlen(s);
} void solve() {
  rep (i,n) cnt[s[i] - 'a']++;
  rep (i,n) cnt[t[i] - 'a']--;
  rep (i,C) if (cnt[i] != 0) { puts("-1"); return; }

  int t_i = 0;
  rep (i,n) {
    cnt[s[i] - 'a']--;
    while (*std::min_element(cnt, cnt+C) < 0) { cnt[t[t_i++] - 'a']++; }
    first[i] = t_i; }
  
  logArray(first, first+n);

  repa (i,n) repa (j,n) {
    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
    if (s[i-1] == t[j-1] && j >= first[i-1]) {
      checkMax(dp[i][j], dp[i-1][j-1] + 1); } }

  printf("%d\n", n - dp[n][n]);
}
