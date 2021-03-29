#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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

constexpr int N = 100005;
Temps::Vector<int> e[N];
int n;

struct Maxs {
  std::pair<int,int> a = std::pair<int,int>(std::numeric_limits<int>::min(), 0);
  std::pair<int,int> b = std::pair<int,int>(std::numeric_limits<int>::min(), 0);

  Maxs() =default;
  explicit Maxs(std::pair<int,int> a, std::pair<int,int> b) : a(a), b(b) {}
  Maxs add(int c) { return Maxs(std::make_pair(a.first+c, a.second), std::make_pair(b.first+c, b.second)); }
  Maxs max(std::pair<int,int> c) {
    if (c >= a) { return Maxs(c,a); }
    else if (c >= b) { return Maxs(a,c); }
    else { return Maxs(a,b); } }
  Maxs max(const Maxs& rhs) { return max(rhs.a).max(rhs.b); }
} w[N];

void dfs0(int u, int f) {
  w[u].a = std::make_pair(0,u);
  for (int v: e[u]) if (v != f) {
    dfs0(v,u); w[u] = w[u].max(w[v].add(1)); } }

void dfs1(int u, int f, Maxs pre = Maxs()) {
  pre = pre.max(std::make_pair(0,u));
  w[u] = w[u].max(pre);
  Temps::Vector<Maxs> sl(1), sr(1);
  sl.reserve(e[u].size() + 1); sr.reserve(e[u].size() + 1);

  for (int v: e[u]) if (v != f) {
    sl.push_back(sl.back().max(w[v].add(1))); }
  sl.pop_back();

  std::reverse(e[u].begin(), e[u].end());
  for (int v: e[u]) if (v != f) {
    sr.push_back(sr.back().max(w[v].add(1))); }
  std::reverse(e[u].begin(), e[u].end());
  sr.pop_back(); std::reverse(sr.begin(), sr.end()); 

  Temps::Vector<Maxs>::iterator il = sl.begin(), ir = sr.begin();
  for (int v: e[u]) if (v != f) {
    dfs1(v,u, pre.max(*il++).max(*ir++).add(1)); } }

int inc_one[N], inc_two[N];
int cnt[N];

void preInit() { } void init() {
  n = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  dfs0(1,0); dfs1(1,0);
  int d = 0; 
  repa (i,n) {
    see(w[i].a, w[i].b);
    checkMax(d, w[i].a.first); }
  for (int i=d;i>=2;i--) {
    memset(cnt, 0, sizeof(cnt));
    int once = 0, twice = 0;
    repa (j,n) {
      if (w[j].b.first >= i) { twice++; }
      else if (w[j].a.first >= i) {
        once++; cnt[w[j].a.second]++; } }
    Maxs max_once_cnt; repa (i,n) max_once_cnt = max_once_cnt.max({cnt[i], i});
    checkMax(max_once_cnt.b.first, max_once_cnt.a.first-1);
    int she_choose = (once + twice + n%2) / 2, tot = once + twice;

    if (she_choose >= 2) {
      if (n % 2 == 0) { 
        if (twice >= 4) { printf("%d\n", i); return; }
        if (tot % 2) { if (tot - 4 > max_once_cnt.b.first) { printf("%d\n", i); return; } }
        else { if (tot - 3 > max_once_cnt.a.first) { printf("%d\n", i); return; } } }
      else { printf("%d\n", i); return; } }
  }
  puts("1");
}
