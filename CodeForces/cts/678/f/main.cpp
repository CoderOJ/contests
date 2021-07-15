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

constexpr int N = 300005;
struct opt_t {
  enum type_t { add=1, remove=2, query=3 } type;
  int a, b, d=-1; };
opt_t opt[N];
int n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i=1; i<=n; ++i) {
    opt[i].type = static_cast<opt_t::type_t>(sc.n());
    if (opt[i].type == opt_t::add) { opt[i].a = sc.nextInt(); opt[i].b = sc.nextInt(); }
    else if (opt[i].type == opt_t::remove) { opt[sc.n()].d = i; }
    else { opt[i].a = sc.nextInt(); } }
  for (int i=1; i<=n; ++i) if (opt[i].type == 1 && opt[i].d == -1) opt[i].d = n + 1;
} 

struct STree {
  struct Node {
    std::vector<std::pair<int,int>> a;
    void build() {
      std::sort(a.begin(), a.end());
      std::vector<std::pair<int,int>> b; 
      auto slope_cmp = [](const std::pair<int,int> &a, const std::pair<int,int> &b) {
        return 1ll * a.second * b.first < 1ll * b.second * a.first; };
      for (auto x: a) {
        while (b.size() >= 2 && slope_cmp(b.end()[-1] - b.end()[-2], x - b.end()[-1])) b.pop_back();
        b.push_back(x); } 
      a = std::move(b); }
    long long query(int k) { 
      if (a.size() == 0) return std::numeric_limits<long long>::min();
      size_t l = 0, r = a.size() - 1;  
      while (l < r) {
        size_t mid = (l + r) / 2;
        const auto sg = a[mid + 1] - a[mid];
        if (sg.second < 1ll * sg.first * -k) { r = mid; }
        else { l = mid + 1; } }
      return 1ll * k * a[l].first + a[l].second; }
  } p[N * 4];
  
  void insert(int u, int l, int r, int il, int ir, std::pair<int,int> val) {
    if (il <= l && r <= ir) { p[u].a.push_back(val); return; }
    int mid = (l + r) / 2;
    if (il < mid) insert(u+u,l,mid, il,ir,val); 
    if (ir > mid) insert(u+u+1,mid,r, il,ir,val); }

  void build(int u, int l, int r) { 
    p[u].build(); int mid = (l + r) / 2;
    if (r - l != 1) { build(u+u, l, mid); build(u+u+1, mid, r); } }
  long long query(int u, int l, int r, int pos, int k) {
    if (r - l == 1) return p[u].query(k);
    int mid = (l + r) / 2; 
    if (pos < mid) { return std::max(p[u].query(k), query(u+u,l,mid, pos,k)); }
    else return std::max(p[u].query(k), query(u+u+1,mid,r, pos,k)); } 
} T;

void solve() 
{
  const int gl = 1, gr = n + 1;
  for (int i=1; i<=n; ++i) {
    if (opt[i].type == opt_t::add) { 
      T.insert(1,gl,gr,i,opt[i].d, std::make_pair(opt[i].a, opt[i].b)); } }
  T.build(1, gl, gr);
  for (int i=1; i<=n; ++i) if (opt[i].type == opt_t::query) {
    long long res = T.query(1,gl,gr, i, opt[i].a);    
    if (res == std::numeric_limits<long long>::min()) { puts("EMPTY SET"); }
    else printf("%lld\n", res); }
}
