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
#define int long long

/** My code begins here **/

constexpr int N = 100005;
int h[N], d[N];
int n, m, k, p;

void preInit() { } 
void init() 
{
  n = sc.n(); m = sc.n(); k = sc.n(); p = sc.n();
  for (int i = 0; i < n; i++) h[i] = sc.n(), d[i] = sc.n();
} 

int value[N];
bool valid(int t) {
  for (int i = 0; i < n; i++) value[i] = t;
  struct info_t { int times, id; };
  struct info_cmp_t { bool operator() (info_t x, info_t y) { return x.times > y.times; } };
  std::priority_queue<info_t, std::vector<info_t>, info_cmp_t> que;
  for (int i = 0; i < n; i++) que.push({value[i] / d[i], i});
  int free_cnt = m * k;
  for (int i = 0; i < m; i++) for (int j = 0; j < k; j++) {
    const auto [times, id] = que.top();
    if (times <= i) return false;
    if (times >= m) break;
    free_cnt--; que.pop(); value[id] += p;
    que.push({value[id] / d[id], id}); }
  int require_cnt = 0;
  for (int i = 0; i < n; i++) {
    value[i] -= d[i] * m;
    see(i, value[i]);
    if (value[i] < h[i])
      require_cnt += (h[i] - value[i] - 1) / p + 1; }
  see(require_cnt, free_cnt);
  return require_cnt <= free_cnt; }

void solve() 
{
  int l = 0, r = 100000000000000;
  while (l < r) {
    int mid = (l + r) / 2;
    see(mid);
    if (valid(mid)) { r = mid; }
    else { l = mid + 1; } }
  std::cout << l << std::endl;
}
