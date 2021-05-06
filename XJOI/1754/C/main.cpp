#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 50005;
int a[N], n, q, num;

namespace agt0 
{
int sum[N];
void main() {
  std::partial_sum(a, a+n, sum+1);
  for (int i=0; i<q; ++i) {
    int l = sc.n() - 1, r = sc.n();
    printf("%d\n", sum[r] - sum[l]); } }
}

namespace bf
{

constexpr int N = 55;

int dp[N][N][2];

int get(int a[], int n, int k) {
  memset(dp[0], 0xcf, sizeof(dp[0]));
  dp[0][0][0] = 0;
  for (int i=0; i<n; ++i)
  {
    dp[i + 1][0][0] = 0, dp[i+1][0][1] = (int)0xcfcfcfcf;
    for (int j=1; j<=n; ++j) {
      dp[i + 1][j][0] = std::max(dp[i][j][0], dp[i][j][1]);
      dp[i + 1][j][1] = std::max(dp[i][j][1], std::max(dp[i][j-1][0], dp[i][j-1][1])) + a[i]; }
  }
  return std::max(dp[n][k][0], dp[n][k][1]); }

void main() {
  for (int i=0; i<q; ++i) {
    int l = sc.n() - 1, r = sc.n(), k = sc.n();
    printf("%d\n", get(a + l, r - l, k)); } }

}

namespace all1n
{

constexpr int N = 10005;
int _dp[2][N][2], (*dp[N])[2];

void get(int a[], int n) {
  memset(_dp[0], 0xcf, sizeof(_dp[0]));
  _dp[0][0][0] = 0;
  for (int i=0; i<=n; ++i) dp[i] = _dp[i % 2];
  for (int i=0; i<n; ++i)
  {
    dp[i + 1][0][0] = 0, dp[i+1][0][1] = (int)0xcfcfcfcf;
    for (int j=1; j<=n; ++j) {
      dp[i + 1][j][0] = std::max(dp[i][j][0], dp[i][j][1]);
      dp[i + 1][j][1] = std::max(dp[i][j][1], std::max(dp[i][j-1][0], dp[i][j-1][1])) + a[i]; }
  } }

void main() {
  get(a, n);
  for (int i=0; i<q; ++i) {
    sc.n(), sc.n(); int k = sc.n();
    printf("%d\n", std::max(dp[n][k][0], dp[n][k][1])); } }

}

void preInit() { } void init() {
  num = sc.n(); n = sc.n(); q = sc.n();
  for (int i=0; i<n; ++i) a[i] = sc.nextInt();
} void solve() {
  if (num == 6) { agt0::main(); return; }
  if (num == 1) { bf::main(); return; }
  if (num == 2 || num == 3) { all1n::main(); return; }
}
