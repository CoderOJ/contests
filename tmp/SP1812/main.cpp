#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

constexpr int N = 100005;
constexpr int M = 10;
constexpr int C = 26;

struct SAM {
protected:
  struct SNode {
    int next[C], size[C], link=-1, len=0;
    SNode () { memset(next, -1, sizeof(next)); memset(size, 0, sizeof(size)); }
  };

  static constexpr int root = 0;
  SNode p[N * 2]; int cnt = root + 1, last = root;

public:
  void insert(std::size_t c) {
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    int pos = last;
    while (pos != -1) {
      if (p[pos].next[c] != -1) { break; }
      p[pos].next[c] = cur;
      pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else {
      int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) {
        p[cur].link = q; }
      else { 
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone;
          pos = p[pos].link; } } }
    last = cur; }
};

struct JSAM : protected SAM {
protected:
  int pos = SAM::root, len = 0;

public:
  using SAM::insert; 
  void move(std::size_t c) {
    while (pos != -1 && p[pos].next[c] == -1) {
      pos = p[pos].link; 
      if (pos != -1) { len = p[pos].len; } }
    if (pos == -1) { pos = 0; len = 0; }
    else { pos = p[pos].next[c]; len++; } }
  inline int getLen() { return len; }
};

JSAM sam[M];
char s[N]; int n;

void preInit() { } void init() { } void solve() {
  while (scanf("%s", s) != EOF) {
    int m=std::strlen(s); rep (j,m) { sam[n].insert(s[j] - 'a'); } 
    n++; }
  n--;
  int m = std::strlen(s);
  int ans = 0; 
  rep (i,m) {
    int pos = std::numeric_limits<int>::max();
    rep (j,n) { sam[j].move(s[i] - 'a'); checkMin(pos, sam[j].getLen()); } 
    checkMax(ans, pos); }
  printf("%d\n", ans);
}
