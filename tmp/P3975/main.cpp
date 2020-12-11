#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

const int N = 500005;
const int C = 26;

struct SAM {
  struct Node {
    std::size_t len = 0, right = 1, size = 1, ref = 0;
    int link = -1, next[C];
    bool vis = 0;
    Node() { memset(next, -1, sizeof(next)); }
  };

  Node p[N*2];
  static constexpr int root = 0;
  int last = root;
  int cnt = root + 1;

  void clear() {
    while (cnt) { p[--cnt] = Node(); }
    cnt = 1; last = 0; }
  void insert(std::size_t c) {
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    int pos = last;
    while (pos != -1) {
      if (p[pos].next[c] != -1) { break; }
      p[pos].next[c] = cur;
      pos = p[pos].link; }
    if (pos == -1) { p[cur].link = 0; }
    else {
      int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[clone].size = 0;
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone;
          pos = p[pos].link; } } }
    last = cur; }

  void solve_0(int k) { 
    std::function<void(int)> dfs = [&](int u) {
      if (p[u].vis) { return; } p[u].vis = 1;
      for (int i=0;i<C;++i) if (p[u].next[i] != -1) { 
        dfs(p[u].next[i]); p[u].right += p[ p[u].next[i] ].right; }
    };
    dfs(root);
    if (k > p[root].right-1) { puts("-1"); return; }
    int u = root;
    while (k) {
      int cho;
      for (cho = 0; cho < C; ++cho) {
        int v = p[u].next[cho];
        if (v == -1) { continue; }
        if (p[v].right < k) { k -= p[v].right; }
        else { break; } }
      putchar('a' + cho);
      u = p[u].next[cho]; 
      k--; 
    } 
  }

  void solve_1(int k) {
    std::function<void()> getSize = [&]() {
      for (int i=1; i<cnt; ++i) p[ p[i].link ].ref ++; 
      std::queue<int> que; for (int i=0; i<cnt; ++i) if (p[i].ref == 0) { que.push(i); } 
      while (!que.empty()) {
        int u = que.front(); que.pop();
        int fa = p[u].link;
        if (fa != -1) {
          p[fa].size += p[u].size;
          p[fa].ref--; if (p[fa].ref==0) { que.push(fa); } } }
    };
    getSize();
    std::function<void(int)> dfs = [&](int u) {
      if (p[u].vis) { return; } p[u].vis = 1;
      p[u].right = p[u].size;
      for (int i=0;i<C;++i) if (p[u].next[i] != -1) { 
        dfs(p[u].next[i]); p[u].right += p[ p[u].next[i] ].right;  }
    };
    dfs(root);
    if (k > p[root].right - p[root].size) { puts("-1"); return; }
    int u = root;
    while (k > 0) {
      int cho;
      for (cho = 0; cho < C; ++cho) {
        int v = p[u].next[cho];
        if (v == -1) { continue; }
        if (p[v].right < k) { k -= p[v].right; }
        else { break; } }
      putchar('a' + cho);
      u = p[u].next[cho]; 
      k -= p[u].size;
    } 
  }
} sam;

char s[N];

void preInit() { } void init() {
  sam.clear();
} void solve() {
  int n, type, k;
  scanf("%s", s); scanf("%d%d", &type, &k);
  n = std::strlen(s);
  rep (i,n) { sam.insert(s[i] - 'a'); }
  if (type == 0) { sam.solve_0(k); }
  else { sam.solve_1(k); }
}
