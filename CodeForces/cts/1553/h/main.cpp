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

constexpr int B = 19;
constexpr int N = 1 << B;
constexpr int inf = std::numeric_limits<int>::max() / 16;
bool vis[N]; int n, k;

struct Trie {
  struct Node {
    int min, max, ans, dep; Node *l, *r;
    Node() =default;
    Node (int dep, Node *l, Node *r) : min(inf), max(-inf), ans(inf), dep(dep), l(l), r(r) {}
    void push_up() { 
      int slen = 1 << l->dep;
      min = std::min(l->min, slen + r->min); max = std::max(l->max, slen + r->max);
      ans = std::min({l->ans, r->ans, slen + r->min - l->max}); }
    void flip(int lim) {
      if (lim == 0) { std::swap(l, r); }
      else { l->flip(lim - 1); r->flip(lim - 1); }
      push_up(); }
  } p[N * 2];
  Node *const root = &p[1];
  void build() {
    for (int i=1<<B; i<(1<<(B+1)); i++) {
      p[i] = Node(0, nullptr, nullptr);
      see(i, i - (1<<B));
      if (vis[i - (1<<B)]) { p[i].min=0; p[i].max=0; } }
    for (int d=B-1; d>=0; d--) {
      for (int i=1<<d; i<(1<<(d+1)); i++) {
        p[i] = Node(B - d, &p[i+i], &p[i+i+1]); 
        p[i].push_up(); 
        see(i, p[i].min, p[i].max, p[i].ans, p[i].dep);
      } } }
} T;

void preInit() {  } 
void init() 
{
  n = sc.n(); k = sc.n();
  for (int i=0; i<n; i++) vis[sc.n()] = true;
} 

int ans[N], cur;
void gray_code(int k) {
  if (k == 0) { see(cur, T.root->ans); ans[cur] = T.root->ans; }
  else gray_code(k - 1);
  T.root->flip(k);
  cur ^= (1 << (B - k - 1));
  if (k == 0) ans[cur] = T.root->ans;
  else gray_code(k - 1);
}

void solve() 
{
  T.build();
  gray_code(B - 1);
  for (int i=0; i<(1<<k); i++) printf("%d ", ans[i]);
}
