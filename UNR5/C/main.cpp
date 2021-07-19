#include <bits/stdc++.h>
#include "/home/jack/code/creats/util.h"
#include "airline.h"

constexpr int N = 2005;
long long dis[N][N];
long long dp[N][N];

long long solve(int n, int x, int y, int q, std::vector<int> P, int L) {
  P.insert(P.begin(), x); P.insert(P.begin(), y); q++;
  for (int i=0; i<q; i++) for (int j=i+1; j<=q; j++) dis[i][j] = distance(P[i], P[j]);
  memset(dp, 0xcf, sizeof(dp));
  dp[1][0] = 0;
  for (int i=1; i<q; i++) {
    for (int j=0; j<=i; j++) {
      checkMax(dp[i + 1][i], dp[i][j] + dis[j][i+1]);
      checkMax(dp[i + 1][j], dp[i][j] + dis[i][i+1]); } }
  return *std::max_element(dp[q], dp[q]+q); }
