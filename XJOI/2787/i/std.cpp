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

constexpr int N = 100005;

struct Matrix {
  int a[2][2];
  Matrix() : a{{0,-0x3f3f3f3f}, {-0x3f3f3f3f,0}} {}
  Matrix(int dp0, int dp1) : a{{dp1, -0x3f3f3f3f}, {dp1, dp0}} {}
  Matrix(int a00, int a01, int a10, int a11) : a{{a00,a01},{a10,a11}} {}
  Matrix operator* (const Matrix &b) {
    return Matrix(
      std::max(a[0][0] + b.a[0][0], a[0][1] + b.a[1][0]),
      std::max(a[0][0] + b.a[0][1], a[0][1] + b.a[1][1]),
      std::max(a[1][0] + b.a[0][0], a[1][1] + b.a[1][0]),
      std::max(a[1][0] + b.a[0][1], a[1][1] + b.a[1][1])); } };

std::vector<int> e[N];
int n;

int dp[N][2], size[N];
void dfs0(int u, int f) {
  dp[u][0] = 0, dp[u][1] = 1; size[u] = 1;
  for (int v: e[u]) if (v != f) {
    dfs0(v, u); size[u] += size[v];
    dp[u][1] = std::max(dp[u][0] + dp[v][1], dp[u][1] + dp[v][0]); 
    dp[u][0] += dp[v][1]; } }

int dpu[N][2];
void dfs1(int u, int f, Matrix up=Matrix()) {
  const auto pos = up * Matrix(dp[u][0], 0, dp[u][1], 0);
  dpu[u][0] = pos.a[0][0], dpu[u][1] = pos.a[1][0];
  std::vector<Matrix> pre, suf;
  pre.reserve(e[u].size() + 1); suf.reserve(e[u].size() + 1);
  pre.push_back(Matrix());
  for (int v: e[u]) if (v != f) {
    pre.push_back(Matrix(dp[v][0], dp[v][1]));
    suf.push_back(Matrix(dp[v][0], dp[v][1])); }
  suf.push_back(Matrix());
  size_t n = pre.size();
  for (size_t i=1; i<n; i++) pre[i] = pre[i] * pre[i-1];
  for (size_t i=n-1; i>0; i--) suf[i-1] = suf[i-1] * suf[i];
  size_t i=0;
  for (int v: e[u]) if (v != f) {
    Matrix tov = up * pre[i] * suf[i + 1] * Matrix(0,0,1,0);
    dfs1(v, u, Matrix(tov.a[0][0], tov.a[1][0]));
    i++; } }

std::pair<int,int> dfs2(int u, int f) {
  std::pair<int,int> res{dpu[u][0] != dpu[u][1], 1};
  for (int v: e[u]) if (v != f) { res = res + dfs2(v, u); }
  return res; }

void preInit() { } 
void init() 
{
  n = sc.n();
  for (int i=1; i<n; ++i) {
    int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} 

void solve() 
{
  dfs0(1, 0);
  const int gmax = dp[1][1];
  long long ans = 0;
  for (int u=1; u<=n; u++) for (int v: e[u]) if (v > u) {
    dfs0(v, u); dfs0(u, v);
    if (dp[v][1] + dp[u][1] > gmax) {
      dfs1(u, v); dfs1(v, u);
      const auto pu = dfs2(u,v), pv = dfs2(v,u);
      ans += 1ll * pu.second * pv.second - 1ll * (pu.first) * (pv.first); } }
  printf("%lld\n", ans);

}
