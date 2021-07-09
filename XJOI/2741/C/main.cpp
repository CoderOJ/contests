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

constexpr int N = 200005;

struct Block {
  int free_cnt = 0;
  std::set<int> white, all;
};

struct BlockRef {
  Block *ref;
  BlockRef() =default;
  BlockRef(Block *ref) : ref(ref) {}
  bool operator< (const BlockRef rhs) const {
    int lhs_val = *(ref->white.begin());
    int rhs_val = *(rhs.ref->white.begin());
    return lhs_val != rhs_val ? lhs_val < rhs_val : ref < rhs.ref; }
};

Block block_pool[N], *bel[N];
std::vector<int> e[N];
std::set<BlockRef> single, multiple;
int n;

void build(int u, Block* to) {
  if (bel[u] != nullptr) return;
  bel[u] = to;
  to->free_cnt++;
  if (u > n) to->white.insert(u);
  to->all.insert(u);
  for (int v: e[u]) build(v, to); }

void merge(Block *a, Block *b) {
  if (a->all.size() < b->all.size())
    std::swap(a, b);
  a->free_cnt += b->free_cnt - 2;
  // assert(a->free_cnt > 0);
  for (int u: b->all) { bel[u] = a; a->all.insert(u); }
  for (int u: b->white) { a->white.insert(u); } }

void add_block(Block *a) {
  if (a->white.size()) {
    if (a->free_cnt > 1) multiple.emplace(a);
    single.emplace(a); } }
void destroy_block(Block *a) {
  multiple.erase({a}); single.erase({a}); }

void preInit() { } 
void init() 
{
  n = sc.n();
  for (int i=1; i<n; ++i) {
    int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} 

void solve() 
{
  for (int i=1; i<=n*2; ++i) build(i, &block_pool[i]);
  for (int i=n+1; i<=n*2; ++i) add_block(bel[i]);
  for (int i=1; i<=n; ++i) printf("%d\n", i);
  for (int i=n; i>=1; i--) {
    BlockRef v = {nullptr};
    see(single.size(), multiple.size());
    if (bel[i]->free_cnt == 1) {
      if (multiple.size()) { v = *multiple.begin(); }
      else { 
        for (const auto x: single) {
          if (x.ref != bel[i]) {
            v = x; } } } } 
    else {
      for (const auto x: single) {
        if (x.ref != bel[i]) {
          v = x; break; } }
      for (const auto x: multiple) {
        if (x.ref != bel[i]) {
          if (v.ref == nullptr || x < v)
            v = x;
          break; } } }
    int ans = *v.ref->white.begin(); printf("%d\n", ans);
    see(v.ref->white);
    see(v.ref->all);
    destroy_block(bel[i]);
    destroy_block(v.ref);
    v.ref->white.erase(ans);
    merge(bel[i], v.ref);
    add_block(bel[i]);
  }
}
