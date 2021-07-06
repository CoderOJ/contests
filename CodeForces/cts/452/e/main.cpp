#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


constexpr int N = 300005;
constexpr int C = 26;

long long ans[N];

struct GSAM {
  struct Node {
    int next[C], link = -1, len = 0, cnt[3] = { 0, 0, 0 }, ref = 0;
    Node() { memset(next, -1, sizeof(next)); } };

  Node p[N * 2];
  static constexpr int root = 0;
  int last = root, cnt = last + 1, rcnt = 0;

  void reset() { last = 0; rcnt++; }

  void insert(int c) {

    int q = p[last].next[c];

    if (q != -1) {
      if (p[q].len == p[last].len + 1) { last = q; }
      else { 
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[last].len + 1;
        p[clone].cnt[0] = p[clone].cnt[1] = p[clone].cnt[2] = 0;
        p[q].link = clone;
        while (last != -1 && p[last].next[c] == q) {
          p[last].next[c] = clone; last = p[last].link; }
        last = clone; } }
    else {
      int cur = cnt++;
      p[cur].len = p[last].len + 1;
      int pos = last;
      while (pos != -1 && p[pos].next[c] == -1) {
        p[pos].next[c] = cur; pos = p[pos].link; }
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
          p[clone].cnt[0] = p[clone].cnt[1] = p[clone].cnt[2] = 0;
          while (pos != -1 && p[pos].next[c] == q) {
            p[pos].next[c] = clone; pos = p[pos].link; } } }
      last = cur; }

    p[last].cnt[rcnt]++; }

  void build() {
    for (int i=1; i<cnt; ++i) p[p[i].link].ref++;    
    std::queue<int> que;
    for (int i=0; i<cnt; ++i) if (p[i].ref == 0) que.push(i);
    while (que.front() != 0) {
      int u = que.front(); que.pop();
      for (int i=0; i<3; ++i) p[p[u].link].cnt[i] += p[u].cnt[i];
      p[p[u].link].ref--; if (p[p[u].link].ref == 0) { que.push(p[u].link); } } }

  void solve() {
    for (int i=1; i<cnt; ++i) {
      long long delta = 1ll * p[i].cnt[0] * p[i].cnt[1] * p[i].cnt[2];
      see(p[i].cnt[0], p[i].cnt[1], p[i].cnt[2]);
      ans[p[i].len] += delta, ans[p[p[i].link].len] -= delta; } }

} gsam;

char s[N];
size_t n = std::numeric_limits<decltype(n)>::max();

void preInit() 
{ 

} 

void init() 
{
  for (int i=0; i<3; ++i) {
    sc.next(s);
    size_t len = std::strlen(s);
    checkMin(n, len);
    for (size_t i=0; i<len; ++i) {
      gsam.insert(s[i] - 'a'); }
    gsam.reset(); }
} 

void solve() 
{
  gsam.build();
  gsam.solve();
  for (size_t i = n; i; i--)
    ans[i - 1] += ans[i];
  for (size_t i = 1; i <= n; ++i) 
    printf("%lld ", ans[i] % 1000000007);
}
