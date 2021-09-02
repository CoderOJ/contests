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

constexpr int N = 200005;
int min_t, max_t, n, m;
std::vector<int> e[N];
std::pair<int,int> inter[N];

void preInit() {  } 
void init() 
{
  min_t = sc.n(), max_t = sc.n();
  n = sc.n(), m = sc.n();
  for (int i = 1; i <= n; i++) 
    inter[i].first = sc.n(), inter[i].second = sc.n();
  for (int i = 0; i < m; i++) { int u = sc.n(), v = sc.n(); e[u].push_back(v); e[v].push_back(u); }
} 

auto intersect(std::pair<int,int> a, decltype(a) b)
{ return std::make_pair(std::max(a.first, b.first), std::min(a.second, b.second)); }
std::pair<int,int> sinter[N];

int color[N];
void dfs(int u, int cur_color, int next_color)
{
  color[u] = cur_color;
  for (int v: e[u]) {
    if (color[v] == -1) dfs(v, next_color, cur_color);
    else if (color[v] != next_color) { puts("IMPOSSIBLE"); exit(0); } }
}

std::vector<int> dist_value;
std::vector<int> at_insert[N * 2], at_erase[N * 2];
void solve() 
{
  std::fill(sinter, sinter + N, std::make_pair(0, max_t));
  std::fill(color, color + N, -1); int cur_color = 0;
  for (int u = 1; u <= n; u++) if (color[u] == -1) dfs(u, cur_color, cur_color + 1), cur_color += 2;
  for (int i = 1; i <= n; i++) sinter[color[i]] = intersect(sinter[color[i]], inter[i]);

  for (int i = 0; i < cur_color; i++) dist_value.push_back(sinter[i].first), dist_value.push_back(sinter[i].second);
  std::sort(dist_value.begin(), dist_value.end()); dist_value.erase(std::unique(dist_value.begin(), dist_value.end()), dist_value.end());
  for (int i = 0; i < cur_color; i++) {
    sinter[i].first = static_cast<int>(std::lower_bound(dist_value.begin(), dist_value.end(), sinter[i].first) - dist_value.begin());
    sinter[i].second = static_cast<int>(std::lower_bound(dist_value.begin(), dist_value.end(), sinter[i].second) - dist_value.begin()); }

  // int c = static_cast<int>(dist_value.size());
  for (int i = 0; i < cur_color; i++) { at_insert[sinter[i].first].push_back(i); at_erase[sinter[i].second + 1].push_back(i); }

  std::set<int> seta_ids;
  std::multiset<int> setb_ls, setb_rs;
  for (int i = 0; i < cur_color; i++) setb_ls.insert(sinter[i].first), setb_rs.insert(sinter[i].second);
  auto move_a2b = [&](int id) { seta_ids.erase(id); setb_ls.insert(sinter[id].first); setb_rs.insert(sinter[id].second); };
  auto move_b2a = [&](int id) { seta_ids.insert(id); setb_ls.erase(setb_ls.find(sinter[id].first)); setb_rs.erase(setb_rs.find(sinter[id].second)); };

  logArray(sinter, sinter + cur_color);
  for (int t = 0; t < cur_color; t++)
  {
    for (int i : at_insert[t]) { 
      if (seta_ids.count(i ^ 1)) {
        if (sinter[i].second < sinter[i^1].second) { move_a2b(i^1); move_b2a(i); } }
      else { move_b2a(i); } }
    for (int i : at_erase[t]) if (seta_ids.count(i)) move_a2b(i);

    see(seta_ids, setb_ls, setb_rs);

    int act_t = dist_value[t];
    int min_b = dist_value[*setb_ls.rbegin()], max_b = dist_value[*setb_rs.begin()];
    see(t, act_t, min_b, max_b);
    if (static_cast<int>(seta_ids.size()) == cur_color / 2 &&
        min_b <= max_b && act_t + min_b <= max_t && act_t + max_b >= min_t)
    {
      puts("POSSIBLE");
      printf("%d %d\n", act_t, std::min(max_b, max_t - act_t));
      for (int i = 1; i <= n; i++) putchar(seta_ids.count(color[i]) ? '1' : '2');
      puts("");
      exit(0);
    }
  }

  puts("IMPOSSIBLE");
}
