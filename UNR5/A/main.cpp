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

constexpr int N = 500005;
struct edge_info_t { int id; bool rev; };
std::multimap<std::pair<int,int>, edge_info_t> ep;
std::multimap<int, int> esp;
int n, m;

struct edge_t { edge_t *next; int v; bool vis = false; };
edge_t e_pool[N * 2], *e[N], *ep_top = e_pool;

void add_edge(int u, int v) {
  ep_top->next = e[u];
  ep_top->v    = v;
  e[u] = ep_top++;
  ep_top->next = e[v];
  ep_top->v    = u;
  e[v] = ep_top++; }
edge_t *get_rev_edge(edge_t *p) {
  return e_pool + (static_cast<uintptr_t>(p - e_pool) ^ 1);
}

void preInit() {  } 
void init() 
{
  m = sc.n(); n = sc.n();
  for (int i=1; i<=m; i++) {
    int k = sc.n();
    if (k == 1) {
      int u = sc.n(); add_edge(0,u);
      esp.insert(std::make_pair(u, i)); }
    else {
      int u=sc.n(), v=sc.n(); add_edge(u,v);
      edge_info_t info = { .id = i, .rev = u > v };
      if (u > v) { std::swap(u, v); }
      ep.insert(std::make_pair(std::make_pair(u, v), info)); } }
} 

std::vector<int> path;

void dfs(int u) {
  for (edge_t *&i=e[u]; i;) {
    if (!i->vis) {
      i->vis = true; get_rev_edge(i)->vis = true;
      int v = i->v; i = i->next; dfs(v); }
    else { i = i->next; } }
  path.push_back(u); }

std::vector<int> id[2];
std::vector<bool> rev[2];
std::vector<int> id2[2];
std::vector<bool> rev2[2];

void solve() 
{
  dfs(0); std::reverse(path.begin(), path.end());
  see(path);
  for (size_t i=0; i+1<path.size(); i++) {
    int u = path[i], v = path[i + 1]; bool r = false; if (u > v) { std::swap(u, v); r = true; }
    if (u == 0) { auto it = esp.find(v); id[i % 2].push_back(it->second); rev[i % 2].push_back(0); esp.erase(it); }
    else { auto it = ep.find(std::make_pair(u,v)); id[i % 2].push_back(it->second.id); rev[i % 2].push_back(it->second.rev ^ r); ep.erase(it); } }
  see(ep.size(), esp.size());
  int spid = -1;
  while (ep.size()) {
    if (ep.size() == 1 || ep.begin()->first != (++ep.begin())->first) {
      assert(spid == -1); spid = ep.begin()->second.id;
      ep.erase(ep.begin()); if (ep.size() == 0) { break; } }
    id2[0].push_back(ep.begin()->second.id); rev2[0].push_back(ep.begin()->second.rev);
    id2[1].push_back((++ep.begin())->second.id); rev2[1].push_back((++ep.begin())->second.rev);
    ep.erase(ep.begin()); ep.erase(ep.begin()); }

  see(id[0].size() + id[1].size());
  std::reverse(id[1].begin(), id[1].end());
  std::reverse(rev[1].begin(), rev[1].end());
  std::reverse(id2[1].begin(), id2[1].end());
  std::reverse(rev2[1].begin(), rev2[1].end());
  for (int x: id2[0]) printf("%d ", x);
  for (int x: id[0]) printf("%d ", x);
  if (spid != -1) { printf("%d ", spid); }
  for (int x: id[1]) printf("%d ", x);
  for (int x: id2[1]) printf("%d ", x);
  puts("");
  for (bool x: rev2[0]) printf("%d ", x);
  for (bool x: rev[0]) printf("%d ", x);
  if (spid != -1) { printf("%d ", 0); }
  for (bool x: rev[1]) printf("%d ", x ^ 1);
  for (bool x: rev2[1]) printf("%d ", x ^ 1);
}
