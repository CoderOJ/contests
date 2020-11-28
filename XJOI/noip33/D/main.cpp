#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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
const int M = 500005;

struct Dsu
{
  int p[N];
  Dsu() { rep(i, N) p[i] = i; }
  int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
  void merge(int u, int v) { p[get(u)] = get(v); }
  bool query(int u, int v) { return get(u) == get(v); }
};

struct Rope
{
  int x, y, l, w;
  bool operator<(const Rope& B) const { return w < B.w; }
};

int n, m;
Rope a[M];
Dsu st;

void
preInit()
{}

void
init()
{
  n = sc.n();
  m = sc.n();
  rep(i, m)
  {
    a[i].x = sc.n();
    a[i].y = sc.n();
    a[i].l = sc.n();
    a[i].w = sc.n();
  }
}

void
solve()
{
  std::sort(a, a + m);
  int link_cnt = 0;
  long long ans = 0;
  rep(i, m) rep(j, a[i].l)
  {
    if (!st.query(a[i].x + j, a[i].y + j)) {
      st.merge(a[i].x + j, a[i].y + j);
      link_cnt++;
      ans += a[i].w;
      if (link_cnt == n - 1) {
        printf("%lld\n", ans);
        return;
      }
    }
  }
  puts("-1");
}
