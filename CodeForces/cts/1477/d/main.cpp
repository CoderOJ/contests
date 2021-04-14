#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

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


const int kN = 5e5 + 5;

int n, m, dg[kN], p[kN], q[kN], siz[kN], rt[kN], col[kN], col_cnt;
std::vector <int> st_E[kN];
std::set <int> S, E[kN];

void Add(int u, int v) {
  E[u].insert(v);
  E[v].insert(u);
  ++dg[u]; ++dg[v]; }
void AddTree(int u, int v) {
  st_E[u].push_back(v);
  st_E[v].push_back(u); }
void Dfs(int u, int p) {
  for(auto v : S) if(!E[u].count(v))
      AddTree(u, v);
  for(auto v : st_E[u]) if(v != p) S.erase(v);
  for(auto v : st_E[u]) if(v != p) Dfs(v, u); }
void Dfs2(int u, int p) {
  bool flag = false;
  if(!col[u]) {
    for(auto v : st_E[u])
      if(!col[v]) flag = true;
    if(flag) {
      col[u] = ++col_cnt;
      rt[col[u]] = u; siz[col[u]] = 1;
      for(auto v : st_E[u]) {
        if(!col[v]) {
          ++siz[col[u]];
          col[v] = col[u]; } } }
    else {
      for(auto v : st_E[u])
        if(col[v]) {
          if(rt[col[v]] == v) {
            ++siz[col[v]]; col[u] = col[v]; }
          else if(siz[col[v]] > 2) {
            col[u] = ++col_cnt;
            rt[col[u]] = u; siz[col[u]] = 2;
            --siz[col[v]];
            col[v] = col[u]; }
          else {
            rt[col[v]] = v;
            col[u] = col[v];
            ++siz[col[u]]; }
          break; } } }
  for(auto v : st_E[u]) if(v != p)
      Dfs2(v, u); }

std::queue <int> que;
std::vector <int> V_col[kN];

void preInit() {}
void init() {
  col_cnt = 0;
  n = sc.n(); m = sc.n();
  for(int i = 1; i <= n; ++i) {
    dg[i] = col[i] = siz[i] = p[i] = q[i] = 0;
    E[i].clear(); st_E[i].clear();
    V_col[i].clear();
    S.insert(i); }
  for(int i = 1; i <= m; ++i) {
    int u, v;
    u = sc.n(); v = sc.n();
    Add(u, v); }
  for(int i = 1; i <= n; ++i)
    if(dg[i] == n - 1) {
      S.erase(i);
      que.push(i); } }

void solve() {
  int tot = n;
  while(!que.empty()) {
    int u = que.front(); que.pop();
    p[u] = q[u] = tot--;
    for(auto v : E[u]) {
      --dg[v];
      if(S.count(v) && dg[v] >= tot - 1) {
        que.push(v); S.erase(v); } } }

  for(int i = 1; i <= n; ++i) if(S.count(i)) { S.erase(i); Dfs(i, 0); }
  for(int i = 1; i <= n; ++i) if(!p[i] && !col[i]) Dfs2(i, 0);
  for(int i = 1; i <= n; ++i) if(col[i]) V_col[col[i]].push_back(i);
  for(int i = 1, s = 1; i <= col_cnt; ++i, ++s) {
    q[rt[i]] = s;
    for(auto u : V_col[i]) {
      if(u != rt[i]) {
        p[u] = s;
        q[u] = ++s; } }
    p[rt[i]] = s; }

  for(int i = 1; i <= n; ++i)
    printf("%d ", p[i]);
  printf("\n");
  for(int i = 1; i <= n; ++i)
    printf("%d ", q[i]);
  printf("\n"); }
