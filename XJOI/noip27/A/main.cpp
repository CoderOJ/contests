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
std::vector <int> e[N];
int n;

void preInit()
{

}

void init()
{
  n = sc.n();
  rep (i,n - 1) {
    int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
}

int cnt[N], sz[N];
void dfs(int u, int f) {
  sz[u] = 1;
  for (int v: e[u]) if (v!=f) {
    dfs(v,u);
    sz[u] += sz[v];
  }
  cnt[ sz[u] ] ++;
}

void solve()
{
  dfs(1,0);
  repb (i,n-1,1) {
    if (n % i != 0) continue;
    int c = 0;
    for (int j = i; j <= n; j += i) {
      c += cnt[j];
    }
    if (c == n / i) {
      printf("%d ", n/i-1);
    }
  }
}
