/**
 * ？？？这种题都拿出来？？？
 * XJOI不愧是你
 */

#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

const int N = 100005;
std::vector<int> e[N];
int ind[N];
int n, m;

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
    int u = sc.n(), v = sc.n();
    e[u].push_back(v);
    ind[v]++;
  }
}

void
solve()
{
  std::priority_queue<int, std::vector<int>, std::greater<int>> que;
  repa(i, n) if (ind[i] == 0) que.push(i);
  std::vector<int> ans;
  while (!que.empty()) {
    int u = que.top();
    que.pop();
    ans.push_back(u);
    for (int v : e[u]) {
      ind[v]--;
      if (ind[v] == 0) {
        que.push(v);
      }
    }
  }
  if (static_cast<int>(ans.size()) < n) {
    puts("-1");
  } else {
    for (int u : ans) {
      printf("%d ", u);
    }
  }
}
