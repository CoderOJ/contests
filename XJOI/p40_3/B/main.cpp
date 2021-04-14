#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"

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

constexpr int L = 200000000;
constexpr int N = 1005;
int n, m;
std::vector < int > son[N];
int type[N], tag, a[N];

void dfs(int cur) {
  for (auto i : son[cur]) {
    if (type[i] == 0) type[i] = 3 - type[cur], dfs(i);
    else if (type[i] + type[cur] != 3) tag = 1; } }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  for (int i = 1; i <= n; i++) son[i].clear();
  for (int i = 1; i <= m; i++) {
    int u = sc.n(), v = sc.n();
    son[u].push_back(v), son[v].push_back(u); }
} void solve() {

  int tag2 = 0, u, v, mid;
  for (int i = 1; i <= n; i++) if (son[i].size() == 2
      && static_cast<int>(son[son[i][0]].size() + son[son[i][1]].size()) == n + 1) {
      for (int j = 1; j <= n; j++) type[j] = 0;
      u = son[i][0], v = son[i][1];
      for (auto j : son[u]) type[j]++;
      for (auto j : son[v]) type[j]++;
      int qwq = 1;
      for (int j = 1; j <= n; j++) { if (type[j] == 0) { qwq = 0; break; } }
      if (qwq) { tag2 = 1; mid = i; son[mid].clear();
        for (std::size_t j = 0; j < son[u].size(); j++) {
          if (son[u][j] == mid) { son[u][j] = son[u].back(); son[u].pop_back(); break; } }
        for (std::size_t j = 0; j < son[v].size(); j++) {
          if (son[v][j] == mid) { son[v][j] = son[v].back(); son[v].pop_back(); break; } }
        break; } }

  for (int i = 1; i <= n; i++) {
    if (son[i].size() == 0) type[i] = -1;
    else type[i] = 0; }

  tag = 0;
  for (int i = 1; i <= n; i++) if (type[i] != -1) {
      type[i] = 1; dfs(i); break; }
  if (tag) { puts("No"); return; }

  std::vector < int > id1, id2;
  for (int i = 1, cnt = 0; i <= n; i++) {
    if (type[i] == 0) { puts("No"); return; }
    else if (type[i] == -1) a[i] = cnt++;
    else if (type[i] == 1) id1.push_back(i);
    else id2.push_back(i); }

  std::sort(id1.begin(), id1.end(), [](int a, int b) {
    return son[a].size() > son[b].size(); });

  for (std::size_t i = 0; i < id1.size(); i++) { a[id1[i]] = L / 4 - 1000 * i; }
  for (std::size_t i = 0; i < id2.size(); i++) {
    a[id2[i]] = a[id1[son[id2[i]].size() - 1]] - L / 2 - i;
    for (auto j : son[id2[i]]) if (a[j] - a[id2[i]] < L / 2) { puts("No"); return; } } 

  if (tag2) { a[u] = a[u] < 0 ? -L / 2 : L / 2; a[v] = a[v] < 0 ? -L / 2 : L / 2; }
  puts("Yes"); printf("%d ", L);
  for (int i = 1; i <= n; i++) printf("%d%c", a[i], " \n"[i == n]); }
