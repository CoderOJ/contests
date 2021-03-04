#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"
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
bool is_forb[N];
Temps::Vector<int> origin_forb;
int n, m, k, deg[N], deg_tot[N];

struct Rational {
  int x=0, y=1;
  Rational() =default;
  Rational(int x, int y): x(x), y(y) {}
  bool operator< (const Rational& rhs) const {
    return 1ll * x * rhs.y < 1ll * y * rhs.x; }
  friend std::ostream& operator<< (std::ostream& out, const Rational& rhs) {
    out << rhs.x << "/" << rhs.y; return out; }
};

Rational make_rational(int id) {
  return Rational(deg[id], deg_tot[id]); }

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); k = sc.n(); origin_forb.reserve(k);
  for ([[maybe_unused]] int i: range(k)) { origin_forb.push_back(sc.n()); }
  for ([[maybe_unused]] int i: range(m)) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
  for (const int u: range(1,n+1)) { deg_tot[u] = e[u].size(); }
} void solve() {

  int time_stamp = 0, best_time = 0;
  Temps::Vector<int> ans; 

  {
    std::fill(deg+1, deg+n+1, 0);
    std::fill(is_forb+1, is_forb+n+1, false);
    for (const int u: origin_forb) { is_forb[u] = true; }
    for (const int u: range(1,n+1)) {
      for (const int v: e[u]) if (!is_forb[v]) { deg[u]++; } }

    std::set<std::pair<Rational,int>> st;
    for (const int u: range(1,n+1)) if (!is_forb[u]) { 
      st.insert(std::make_pair(make_rational(u), u)); }

    Rational best;
    while (!st.empty()) {
      const auto [low, u] = *st.begin();
      if (checkMax(best, low)) { best_time = time_stamp; }
      st.erase(st.begin()); is_forb[u] = true; time_stamp++;
      for (const int v: e[u]) if (!is_forb[v]) {
        st.erase(st.find(std::make_pair(make_rational(v), v))); 
        deg[v]--; st.insert(std::make_pair(make_rational(v), v)); } }
  }
  
  {
    std::fill(deg+1, deg+n+1, 0);
    std::fill(is_forb+1, is_forb+n+1, false);
    for (const int u: origin_forb) { is_forb[u] = true; }
    for (const int u: range(1,n+1)) {
      for (const int v: e[u]) if (!is_forb[v]) { deg[u]++; } }

    std::set<std::pair<Rational,int>> st;
    for (const int u: range(1,n+1)) if (!is_forb[u]) { 
      st.insert(std::make_pair(make_rational(u), u)); }

    for ([[maybe_unused]] int i: range(best_time)) {
      const auto [low, u] = *st.begin();
      st.erase(st.begin()); is_forb[u] = true; time_stamp++;
      for (const int v: e[u]) if (!is_forb[v]) {
        st.erase(st.find(std::make_pair(make_rational(v), v))); 
        deg[v]--; st.insert(std::make_pair(make_rational(v), v)); } }

    ans.reserve(st.size());
    for (const auto& i: st) { ans.push_back(i.second); }
  }

  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << std::endl;
  std::ostream_iterator<int> out(std::cout, " ");
  std::copy(ans.begin(), ans.end(), out);

}
