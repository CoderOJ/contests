#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

constexpr int N = 1000005;
constexpr int C = 26;
constexpr int MOD = 1e9 + 7;
typedef Intm::Intm<MOD> Int;

struct ESAM {
protected:
  struct Node {
    int next[C], link=-1, len=0, id=0, vis=0;
    Int tot = 1;
    Node () { memset(next, -1, sizeof(next)); }
  };

  Node p[N*2];
  int root = 0;
  int last = root, cnt = root+1;
  int roots[N], id = 0;

public:
  ESAM () { memset(roots, 0, sizeof(roots)); }
  void reset() { 
    last = root = cnt++; id++; 
    p[root].id = id; roots[id] = root; }
  void insert(std::size_t c) {
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    p[cur].id = id;  
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
  void build() {
    for (int i=roots[id-1]-1; i>=0; --i) for (int j=0; j<C; ++j) {
      if (p[i].next[j] == -1) { 
        p[i].next[j] = p[ roots[p[i].id+1] ].next[j]; } } }
  Int solve() {
    std::function<Int(int)> dfs = [&](int u) {
      if (p[u].vis) { return p[u].tot; } p[u].vis = 1;
      for (int i=0; i<C; ++i) {
        if (p[u].next[i] != -1) { 
          slog("transfer %d to %d on character '%c'\n", u, p[u].next[i], 'a'+i);
          p[u].tot += dfs(p[u].next[i]); } }
      slog("THE ANSWER OF %d is %u\n", u, static_cast<unsigned>(p[u].tot));
      return p[u].tot; };
    return dfs(0); }
} sam;

void preInit() { } void init() { } void solve() {
  static char s[N];
  int n; scanf("%d", &n);
  for (int i=0; i<n; ++i) { 
    scanf("%s", s); int l = std::strlen(s); 
    for (int i=0; i<l; ++i) { sam.insert(s[i] - 'a'); }
    sam.reset(); }
  sam.build();
  printf("%u\n", static_cast<unsigned>(sam.solve()));
}
