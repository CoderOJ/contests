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

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

const int N = 100005;
std::vector<int> e[N];
int n, k;

void
preInit()
{}

void
init()
{
  n = sc.n();
  k = sc.n();
  repa(i, n) e[i].clear();
  repa(i, n - 1) e[sc.n()].push_back(i + 1);
}

int match_cnt;
int spare[N];

void
dfs(int u, int f)
{
  spare[u] = 1;
  for (int v : e[u])
    if (v != f) {
      dfs(v, u);
      if (spare[u] && spare[v]) {
        spare[u] = 0;
        match_cnt++;
      }
    }
}

void
solve()
{
  match_cnt = 0;
  repa(i, n) spare[i] = 0;
  dfs(1, 0);
  int reserve = 0;
  while (match_cnt && k>1) {
    k -= 2;
    match_cnt--;
    reserve++;
  }
  reserve += k;
  printf("%d\n", reserve);
}
