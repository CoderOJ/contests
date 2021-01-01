#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

constexpr int N = 100005;
constexpr int C = 10;

struct GSAM {
  struct Node {
    int next[C], link=-1, len=0;
    Node() { memset(next, -1, sizeof(next)); }
  };

  Node p[N*40];
  static constexpr int root = 0;
  int cnt = root + 1;

  int insert(int c, int last) {
    if (p[last].next[c] != -1 && p[last].len + 1 == p[p[last].next[c]].len) {
      return p[last].next[c]; }
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
      p[pos].next[c] = cur; pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else {
      int q = p[pos].next[c];
      if (p[pos].len + 1 == p[q].len) { p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[cur].link = p[q].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    return cur; }

  long long dcount() {
    long long res = 0;
    repa (i,cnt-1) { res += p[i].len - p[p[i].link].len; }
    return res; }
} gsam;

std::vector<int> e[N]; int w[N], vis[N], n;

void bfs(int root) {
  memset(vis, 0, sizeof(vis)); vis[root] = 1;
  std::queue<std::pair<int,int>> que; que.push(std::make_pair(root, gsam.insert(w[root], GSAM::root)));
  while (!que.empty()) {
    int u = que.front().first, p = que.front().second; que.pop();
    for (int v: e[u]) if (!vis[v]) {
      vis[v] = 1; que.push(std::make_pair(v, gsam.insert(w[v], p))); } }
}

void preInit() { } void init() {
  n = sc.n(); sc.n(); repa (i,n) w[i] = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  repa (i,n) if (e[i].size() == 1) { bfs(i); }
  printf("%lld\n", gsam.dcount());
}
