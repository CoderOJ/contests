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

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 300005;
constexpr int C = 26;

long long ans_kind[N], ans_max[N];

struct SAM {
  struct Node {
    int next[C], link=-1, len=0, size=0, val;
    Temps::Vector<int> e; int min_val, max_val;
    Node() { memset(next, -1, sizeof(next)); }
  } p[N * 2];
  static constexpr int root = 0;
  int last = root, cnt = last + 1;

  void insert(std::size_t c, int val) {
    int cur = cnt++;
    p[cur].len = p[last].len + 1; p[cur].val = val; p[cur].size = 1;
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
      p[pos].next[c] = cur; pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else { int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else { 
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[clone].size = 0; p[clone].val = 0;
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    last = cur; }

  void build() {
    for (int i: range(1,cnt)) { p[p[i].link].e.push_back(i); } }
  void dfs(int u = root) {
    p[u].min_val = p[u].max_val = p[u].val;
    for (int v: p[u].e) { dfs(v);
      if (p[u].size == 0) {
        p[u].size += p[v].size; p[u].min_val = p[v].min_val; p[u].max_val = p[v].max_val; }
      else {
        ans_kind[p[u].len] += 1ll * p[u].size * p[v].size; p[u].size += p[v].size; 
        checkMax(ans_max[p[u].len], 1ll * p[u].max_val * p[v].max_val); checkMax(p[u].max_val, p[v].max_val);
        checkMax(ans_max[p[u].len], 1ll * p[u].min_val * p[v].min_val); checkMin(p[u].min_val, p[v].min_val); } } }
} sam;

int n, val[N];
char s[N];


void preInit() { } void init() {
  n = sc.n(); sc.next(s);
  for (int i: range(n)) { val[i] = sc.nextInt(); }
  std::reverse(s, s+n); std::reverse(val, val+n);
  std::fill(ans_max, ans_max+n, std::numeric_limits<long long>::min());
} void solve() {
  for (int i: range(n)) { sam.insert(s[i] - 'a', val[i]); }
  sam.build(); sam.dfs();
  for (int i: range(n-1,0,-1)) {
    ans_kind[i-1] += ans_kind[i];
    checkMax(ans_max[i-1], ans_max[i]); }
  for (int i: range(n)) {
    if (ans_kind[i]) { printf("%lld %lld\n", ans_kind[i], ans_max[i]); }
    else { puts("0 0"); } }
}
