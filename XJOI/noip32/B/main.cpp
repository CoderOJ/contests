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

const int N = 200005;
const int B = 20;
int a[N], ord_a[N], n;

int lg[N];

void
preInit()
{
  lg[1] = 0;
  repi(i, 2, N - 1) lg[i] = lg[i >> 1] + 1;
}

void
init()
{
  n = sc.n();
  rep(i, n) a[i] = sc.n();
  rep(i, n) ord_a[a[i]] = i;
}

struct ST
{
  int a[B][N];
  void init(int _a[], int n)
  {
    rep(i, n) a[1][i] = _a[i];
    repi(b, 1, B - 2)
    {
      int l = 1 << b;
      int up = n - l;
      rep(i, up) a[b + 1][i] = std::min(a[b][i], a[b][i + l]);
    }
  }
  int query(int l, int r)
  {
    int len_b = lg[r - l + 2];
    int len = 1 << len_b;
    return std::min(a[len_b][l], a[len_b][r - len + 2]);
  }
} st;

struct inter
{
  int l, r;
  int sl, sr;
  inter(int l = 0, int r = 0)
    : l(l)
    , r(r)
    , sl(0)
    , sr(0)
  {}
  bool operator<(const inter& b) const
  {
    return std::pair<int, int>(a[sl], a[sr]) >
           std::pair<int, int>(a[b.sl], a[b.sr]);
  }
  void set()
  {
    sl = ord_a[st.query(l, r - 1)];
    sr = ord_a[st.query(sl + 1, r)];
  }
};

void
solve()
{
  st.init(a, n);
  std::priority_queue<inter> que;
  std::vector<int> ans;
  inter inital(0, n - 1);
  inital.set();
  que.push(inital);
  while (!que.empty()) {
    auto u = que.top();
    que.pop();
    ans.push_back(a[u.sl]);
    ans.push_back(a[u.sr]);
    if (u.l < u.sl) {
      inter ins(u.l, u.sl - 1);
      ins.set();
      que.push(ins);
    }
    if (u.sl + 1 != u.sr) {
      inter ins(u.sl + 1, u.sr - 1);
      ins.set();
      que.push(ins);
    }
    if (u.sr != u.r) {
      inter ins(u.sr + 1, u.r);
      ins.set();
      que.push(ins);
    }
  }
  for (int i : ans)
    printf("%d ", i);
}
