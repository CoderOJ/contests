#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

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

const int N = 1000005;
int n, max_c;
int skip[N], cost[N];
int ans[N];

void preInit()
{

}

void init()
{
  n = sc.n(); max_c = sc.n();
  rep (i,n) { skip[i] = sc.n(); cost[i] = sc.n();}
}

void solve()
{
  memset(ans, 0x3f, sizeof(ans));
  ans[0] = 0;
  rep (i,n)
  {
    int posid = i + skip[i];
    int posans = ans[i] + cost[i];
    while (posid <= n)
    {
      checkMin(ans[posid], posans);
      posid += skip[i];
      posans += cost[i];
    }
  }
  repa (i,n) printf("%d ", (ans[i] == 0x3f3f3f3f) ? -1 : ans[i]);
}
