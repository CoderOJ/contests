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

constexpr int N = 100005;
constexpr int gl = 0, gr = N / 5;

struct STree {
  struct Node {
    int min=0, cnt=1, add=0;
    inline void push_up(const Node l, const Node r) {
      if (l.min == r.min) { min = l.min; cnt = l.cnt + r.cnt; }
      else if (l.min < r.min) { min = l.min; cnt = l.cnt; }
      else { min = r.min; cnt = r.cnt; } }
    inline void push_add(int delta) { min+=delta; add+=delta; }
    void push_down(Node &l, Node &r) { l.push_add(add); r.push_add(add); add=0; return; }
  } p[N];
  
  void init(int u, int l, int r) {
    if (r - l == 1) { return; }
    int mid = (l + r) / 2; init(u+u, l, mid); init(u+u+1, mid, r);
    p[u].push_up(p[u + u], p[u + u + 1]); }
  void modify(int u, int l, int r, int ml, int mr, int delta) {
    if (ml <= l && r <= mr) { p[u].push_add(delta); return; }
    p[u].push_down(p[u + u], p[u + u + 1]);
    int mid = (l + r) / 2;
    if (ml < mid) modify(u + u, l, mid, ml, mr, delta);
    if (mr > mid) modify(u + u + 1, mid, r, ml, mr, delta); 
    p[u].push_up(p[u + u], p[u + u + 1]); }
  int query() { return p[1].min == 0 ? p[1].cnt : 0; }
} T;

struct SFill {
  struct delta_t { int x, l, r, d; };
  Vector<delta_t> a;

  void insert(int x0, int x1, int y0, int y1) {
    a.push_back({x0, y0, y1, 1}).push_back({x1, y0, y1, -1}); }
  long long doit() {
    std::sort(a.begin(), a.end(), [](const delta_t &a, const delta_t &b) { 
      return a.x < b.x; });
    long long ans = 0;
    int last = -0x3f3f3f3f;
    for (const auto& i: a) {
      ans += 1ll * (i.x - last) * (gr-gl - T.query()); last = i.x;
      T.modify(1, gl, gr, i.l, i.r, i.d); }
    return ans; }
} S[5][5];

int n, q;

void preInit() { T.init(1, gl, gr); }
void init() 
{ n = sc.n(); q = sc.n(); } 

void solve() 
{
  for (int _=0; _<q; ++_) {
    int x0=sc.n(), y0=sc.n(), dx=sc.n()-x0+1, dy=sc.n()-y0+1;
    for (int j=0; j<std::min(5,dy); j++) {
      for (int i=0; i<std::min(5,dx); i++) {
        int id = j * dx + i;
        if (id % 5 != 0) continue;
        S[(x0+i)%5][(y0+j)%5].insert((x0+i)/5, (x0+i)/5 + (dx-i+4)/5, (y0+j)/5, (y0+j)/5 + (dy-j+4)/5); } } }
  long long ans = 0;
  for (int i=0; i<5; ++i) {
    for (int j=0; j<5; ++j) {
      ans += S[i][j].doit(); } }
  std::cout << ans << std::endl; 
}
