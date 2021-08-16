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

constexpr int N = 200005;
constexpr int B = 107;
int fa[N], dep_cnt[N], depth[N], n;
int f[N + 1], cv[N + 1], g[N + 1];
long long ans[N + 1];

void preInit() {  }
void init() {
  n = sc.n();
  for (int v = 2; v <= n; v++)
    fa[v] = sc.n(); }

void solve() {
  depth[1] = 0;
  for (int v = 2; v <= n; v++) {
    depth[v] = depth[fa[v]] + 1;
    dep_cnt[depth[v]]++; }
  for (int i = n - 1; i >= 1; i--)
    dep_cnt[i] += dep_cnt[i + 1];

  for (int v = 1; v <= n; v++) cv[v] = v;
  for (int d = 1; d <= B; d++) {
    for (int v = 1; v <= n; v++)
      f[v] = g[v] = 0;
    for (int v = n; v > 1; v--) { f[v]++;
      if (cv[v] != 1) { g[cv[v]] += f[v]; cv[v] = fa[cv[v]]; }
      ans[d] += 1ll * f[fa[v]] * g[v];
      f[fa[v]] += g[v]; } }

  std::vector<int> h[N + 1];
  for (int v = n; v > 1; v--) {
    h[v].push_back (1);
    if (h[fa[v]].size() < h[v].size() )
      std::swap (h[v], h[fa[v]]);

    int a_n = (int) h[v].size();
    int *a = h[v].data();
    int b_n = (int) h[fa[v]].size();
    int *b = h[fa[v]].data();

    if (a_n > B && b_n > B) {
      for (int d = B + 1; d <= a_n; d++) {
        int s_a = 0;
        for (int i = d; i <= a_n; i += d) s_a += a[a_n - i];
        int s_b = 0;
        for (int i = d; i <= b_n; i += d) s_b += b[b_n - i];
        ans[d] += 1ll * s_a * s_b; } }

    for (int i = 1; i <= a_n; i++)
      b[b_n - i] += a[a_n - i];
    h[v].clear(); }

  for (int i = n; i >= 1; i--)
    for (int j = i + i; j <= n; j += i)
      ans[i] -= ans[j];
  for (int i = 1; i <= n; i++) ans[i] += dep_cnt[i];
  for (int i = 1; i < n; i++) printf ("%lld\n", ans[i]);
}

