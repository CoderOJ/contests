#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/Vector.h"
#include "/home/jack/code/creats/util.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
#include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 100005;
Temps::Vector<int> e[N];
int a[N], n;

void merge(std::map<int,int>& a, const std::map<int,int>& b) {
  for (const auto x: b) { a[x.first] += x.second; } }

namespace Chain {
bool check() {
  if (e[1].size() != 1) { return false; }
  repa (i,n) if (e[i].size() > 2) { return false; }
  return true;
}

int a[N];
void dfs(int u, int f, int dep) {
  a[dep] = ::a[u];
  for (int v: e[u]) if (v!=f) { 
    dfs(v,u,dep + 1); } }

void main() {
  dfs(1,0,0);
  constexpr int B = 918;
  int a_min = *std::min_element(a, a+n);
  int a_max = *std::max_element(a, a+n);
  int len = a_max - a_min + 1;
  long long ans = 0;
  for (int l=0; l<n; l+=B) {
    int r = std::min(l+B, n);
    Polys::CPoly L(len), R(len);
    for (int i=0;i<l;++i) { L[a[i] - a_min] += 1; }
    for (int i=r;i<n;++i) { R[a[i] - a_min] += 1; }
    Polys::CPoly T = L * R;
    for (int i=l;i<r;++i) { R[a[i] - a_min] += 1; }
    for (int i=l; i<r; ++i) {
      R[a[i] - a_min] -= 1;
      int ai = a[i] - a_min * 2;
      if (0 <= ai && ai < len) { ans += (long long)std::round(T[ai].r); }
      for (int j=l; j<r; ++j) {
        if (j < i) { int p=a[i]-a[j]-a_min; if (0<=p && p<len) { ans += (long long)std::round(R[p].r); } }
        if (j > i) { int p=a[i]-a[j]-a_min; if (0<=p && p<len) { ans += (long long)std::round(L[p].r); } } }
      see(i,ans);
      L[a[i] - a_min] += 1; } }
  printf("%lld\n", ans); }

}

namespace bf {

int ws[N], size[N];
void dfs0(int u, int f) {
  size[u] = 1; ws[u] = -1; int ws_w=0;
  for (int v: e[u]) if (v != f) {
    dfs0(v,u); size[u] += size[v]; 
    if (checkMax(ws_w, size[v])) { ws[u] = v; } } }

long long ans = 0;
Temps::Vector<int> anc;
std::map<int,int> st[N];

void dfs1(int u, int f) noexcept {
  anc.push_back(u);
  if (ws[u] != -1) { dfs1(ws[u],u); 
    st[u] = std::move(st[ws[u]]); }
  for (int v: e[u]) if (v!=f && v!=ws[u]) {
    dfs1(v,u); merge(st[u], st[v]); }
  anc.pop_back();
  for (int p: anc) { 
    if (st[u].count(a[u] - a[p])) {
      ans += st[u][a[u]-a[p]]; } }
  st[u][a[u]]++; }

void main() {
  dfs0(1,0); dfs1(1,0);
  printf("%lld\n", ans);
}

}

void preInit() { } void init() {
  n = sc.n();
  repa (i,n) { a[i] = sc.nextInt(); }
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  bf::main(); 
}
