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

constexpr int N = 2000005;
std::vector<std::pair<int,int>> e[N];
std::mt19937_64 rd(20050610);
int n, m;

void preInit() { } 
void init() 
{
  n = sc.n(); m = sc.n();
  for (int i=0; i<m; i++) {
    int u=sc.n(), v=sc.n();
    e[u].push_back({v, i}); e[v].push_back({u, i}); }
} 

int dep[N], tag[N], up_id[N];
uint64_t eval[N], uval[N];
int odd_cnt;
uint64_t odd_sum;

void dfs(int u, int f) {
  dep[u] = dep[f] ^ 1; tag[u] = 1;
  for (const auto& i: e[u]) if (i.first != f) {
    const int v = i.first, id = i.second;
    if (tag[v] == 0) { up_id[v] = id; dfs(v, u); uval[u] ^= uval[v]; }
    else if (tag[v] == 1) { 
      uval[u] ^= (eval[id] = rd());
      if (dep[v] == dep[u]) { odd_cnt++; odd_sum ^= eval[id]; } }
    else { uval[u] ^= eval[id]; } }
  if (f != 0) eval[up_id[u]] = uval[u];
  tag[u] = -1; }

void solve() 
{
  for (int i=1; i<=n; i++) if (tag[i] == 0) dfs(i, 0);
  see(odd_cnt, odd_sum);
  if (odd_cnt == 0) { puts("1"); return; }
  int single_cnt = 0;
  for (int i=0; i<m; i++) single_cnt += eval[i] == odd_sum;
  if (single_cnt != 0) { printf("%d\n", single_cnt); return; }
  logArray(eval, eval + m);
  std::sort(eval, eval + m);
  long long ans = 0;
  for (int i=0; i<m; i++) {
    ans += std::upper_bound(eval, eval + m, odd_sum ^ eval[i]) -
           std::lower_bound(eval, eval + m, odd_sum ^ eval[i]); }
  std::cout << ans / 2 << std::endl;
}
