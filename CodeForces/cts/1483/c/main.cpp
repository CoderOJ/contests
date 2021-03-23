
#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"

#include "/home/jack/code/creats/STree.h"
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

constexpr int N = 300005;
int a[N], b[N], pre[N], n;
long long pv[N], dp[N];

struct Node
{
  long long val;
  long long tg;
  Node(long long val = 0, long long tg = 0)
    : val(val)
    , tg(tg)
  {}
  void update(long long _val)
  {
    val += _val;
    tg += _val;
  }
  void pushUp(Node a, Node b) { val = std::max(a.val, b.val); }
  void pushDown(Node& a, Node& b)
  {
    a.val += tg;
    b.val += tg;
    a.tg += tg;
    b.tg += tg;
    tg = 0;
  }
};

STree::STree<N, Node> T;

void preInit() { } void init() {
  n = sc.n();
  for (int i: range(n)) a[i] = sc.n();
  for (int i: range(n)) b[i] = sc.nextInt();
  std::stack<std::pair<int,int>> le;
  le.push({-1,-1});
  for (int i: range(n)) {
    while (le.top().first > a[i]) { le.pop(); }
    pre[i] = le.top().second;
    le.push({a[i], i}); }
} void solve() {
  T.setLR(-2, n+2);
  T.modify(-1,-1,0);
  for (int i: range(n)) {
    pv[i] = T.query(pre[i], i-1).val + b[i];
    if (pre[i] != -1)  { checkMax(pv[i], pv[pre[i]]); }
    dp[i] = pv[i];
    T.modify(i,i,dp[i]); }
  printf("%lld\n",dp[n-1]);
}
