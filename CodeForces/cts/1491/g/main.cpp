#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"
#include "/home/jack/code/creats/pipe.h"

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

constexpr int N = 200005;
int to[N], n, pos[N];
bool vis[N];
std::vector<Vector<int>> circs;

std::vector<std::pair<int,int>> opts;
auto swap = [](int& a, int& b) {
  opts.push_back({pos[a], pos[b]}); 
  std::swap(pos[a], pos[b]); std::swap(a,b); };

void dfs(Vector<int> &output, int u) {
  vis[u] = true; output.push_back(to[u]);
  if (!vis[to[u]]) { dfs(output, to[u]); } }

void handle_two(Vector<int> &&a, Vector<int> &&b) {
  swap(a[0], b[0]);    
  for (std::size_t i=1; i<a.size(); ++i) swap(a[i], b[0]);
  for (std::size_t i=1; i<b.size(); ++i) swap(b[i], a[0]);
  swap(a[0], b[0]); }

void handle_one(Vector<int> &a) {
  assert(a.size() >= 3);
  see(a);
  swap(a.back(), a[0]);
  swap(a[0], a[1]); 
  swap(a.back(), a[1]);
  for (std::size_t i=2; i<a.size()-1; ++i) swap(a[0], a[i]);
  swap(a.back(), a[0]);
}

Vector<int> find_spare(const Vector<int>& a) {
  assert(a.size() < (unsigned)n);
  Vector<bool> vis(n, false);
  for (int i: a) vis[i] = true;
  for (int i=0;;++i) if (!vis[i])
    return Vector<int>(1,i);
}

void preInit() { } void init() {
  n = sc.n();
  for (int i: range(n)) { to[i] = sc.n() - 1; pos[to[i]] = i; }
} void solve() {
  for (int i: range(n)) if (!vis[i]) { 
    circs.push_back({}); dfs(circs.back(), i); 
    if (circs.back().size() <= 1ul) { circs.pop_back(); } }

  for (std::size_t i=0; i+1<circs.size(); i+=2) 
    handle_two(std::move(circs[i]), std::move(circs[i + 1]));

  if (circs.size() % 2 == 1) {
    if (circs.back().size() > 2) handle_one(circs.back());
    else handle_two(std::move(circs.back()), find_spare(circs.back())); }

  std::cout << opts.size() << std::endl;
  for (const auto& [u,v]: opts) std::cout << u+1 << " " << v+1 << std::endl;
}
