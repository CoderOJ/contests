#include "/home/jack/code/creats/loop.h"
#include <bits/stdc++.h>

const int STATE_PENDING = -1;
const int STATE_INQUEUE = -2;
const int STATE_INVALID = -3;

const int N = 1005;
int dp[N][N], n, m;

void dfs(int a, int b) {
  if (dp[a][b] == STATE_INQUEUE) {
    dp[a][b] = STATE_INVALID; return; }
  if (dp[a][b] == STATE_PENDING) {
    dp[a][b] = STATE_INQUEUE;
    int c = (a + b) % m;
    dfs(b, c); 
    dp[a][b] = dp[b][c] == STATE_INVALID ? STATE_INVALID : dp[b][c] + 1; } }

void preInit() { 
#ifndef __LOCALE__
  freopen("fib.in", "r", stdin);
  freopen("fib.out", "w", stdout);
#endif
} void init() {
  scanf("%d%d", &n, &m);
  memset(dp, STATE_PENDING, sizeof(dp));
  memset(dp[0], 0, sizeof(dp[0]));
  rep (i,m) rep (j,m) if (dp[i][j] == STATE_PENDING) { dfs(i, j); }
} void solve() {
  rep (i,n) {
    int x, y; scanf("%d%d", &x, &y);
    printf("%d\n", dp[x][y] == STATE_INVALID ? -1 : dp[x][y]); }
}

int main() { preInit(); init(); solve(); return 0; }
