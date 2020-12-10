#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

const int N = 100005;

struct SAM {
  struct Node {
    std::map<int, int> next;
    int link=-1, len=0;
  };

  Node p[N*2];
  static constexpr int root = 0;
  int last = root, cnt = root+1;
  std::size_t count = 0;

  void insert(int c) {
    int cur = cnt++, pos = last;
    p[cur].len = p[pos].len + 1;
    while (pos != -1) {
      if (p[pos].next.count(c)) { break; }
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
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next.count(c) && p[pos].next[c] == q) {
          p[pos].next[c] = clone; 
          pos = p[pos].link; } } }
    count += p[cur].len - p[ p[cur].link ].len;
    last = cur;
  }
} sam;


void preInit() { } void init() { } void solve() {
  int n = sc.n();
  rep (i,n) { int u=sc.n(); sam.insert(u); printf("%lu\n", sam.count); }
}
