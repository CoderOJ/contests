#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

// #include "/home/jack/code/creats/STree.h"
#include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

using namespace Tree;
const int N = 1000005;
TreeBase<N> T;
int n;

void preInit()
{

}

void init()
{
  n = sc.n();
  rep (i,n-1) { T.addEdge(sc.n(), sc.n()); }
}

int thr;
int dfs(int u, int f) {
  int sz = 1;
  auto vs = T.getNodes(u);
  for (int v: vs) if (v!=f) {
    sz += dfs(v,u);
  }
  if (sz == thr) { sz = 0; }
  return sz;
}

void solve()
{
  repi (i,2,n) {
    if (n % 2 != 0) continue;
    thr = i;
    if (dfs(1,0) == 0) {
      printf("%d ", i-1);
    }
  }
}
