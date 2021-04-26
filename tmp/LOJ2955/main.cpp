#include "/home/jack/code/creats/gpl.h"

#define SCANNER_H_CUSTOM
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

#define long long long 
constexpr int N = 100005;
constexpr long inf = 0x3f3f3f3f3f3f3f3f;
constexpr long inf2 = 1e10;

struct Matrix {
  long a[2][2] __attribute__ ((aligned));
  Matrix() =default;
  constexpr Matrix(long a, long b) : a{{inf, a}, {b, b}} {}
  constexpr Matrix(long a, long b, long c, long d) : a{{a,b}, {c,d}} {}

  constexpr long *operator[](long id) { return a[id]; }
  constexpr const long *operator[](long id) const { return a[id]; }

  constexpr Matrix operator* (const Matrix& rhs) const {
    return {
      std::min(a[0][0] + rhs[0][0], a[0][1] + rhs[1][0]),
      std::min(a[0][0] + rhs[0][1], a[0][1] + rhs[1][1]),
      std::min(a[1][0] + rhs[0][0], a[1][1] + rhs[1][0]),
      std::min(a[1][0] + rhs[0][1], a[1][1] + rhs[1][1]) }; }
};

struct Node {
  Node *f, *s[2];
  Matrix tot; long val[2];

  bool is_root() const {
    return f == nullptr || (f->s[0] != this && f->s[1] != this); }
  bool get_son() const { return f->s[1] == this; }
  void push_up() {
    tot = Matrix(val[0], val[1]);
    if (s[0]) { tot = s[0]->tot * tot; }
    if (s[1]) { tot = tot * s[1]->tot; } }
  void rotate() {
    Node *const uu=this, *const ff=f, *const aa=ff->f;
    const bool ss = get_son();
    if (!ff->is_root()) { aa->s[ff->get_son()] = uu; }
    ff->f = uu; ff->s[ss] = uu->s[!ss];
    uu->f = aa; uu->s[!ss] = ff;
    if (ff->s[ss]) { ff->s[ss]->f = ff; }
    ff->push_up(); }
  void splay() {
    while (!is_root()) {
      if (f->is_root()) { rotate(); break; }
      (is_root() == f->is_root() ? f : this)->rotate(); rotate(); } 
    push_up(); }
  void access() {
    Node *uu=this, *ss=nullptr;
    while (uu) {
      uu->splay();
      if (uu->s[1]) {
        uu->val[0] +=                               uu->s[1]->tot[1][1];
        uu->val[1] += std::min(uu->s[1]->tot[0][1], uu->s[1]->tot[1][1]); }
      uu->s[1] = ss;
      if (uu->s[1]) {
        uu->val[0] -=                               uu->s[1]->tot[1][1];
        uu->val[1] -= std::min(uu->s[1]->tot[0][1], uu->s[1]->tot[1][1]); }
      uu->push_up();
      ss = uu, uu = uu->f; } }
  long modify(long delta) {
    access(); splay();
    val[1] += delta; push_up(); 
    return std::min(tot[0][1], tot[1][1]); }
} p[N] __attribute__ ((aligned));

char trash[10];
int n, m, w[N];
std::vector<int> e[N];

inline void fix(long &a) { a = a >= inf ? inf : a; }

std::pair<long,long> dfs(int u, int f) {
  std::pair<long,long> dp(0, w[u]);
  for (const int v: e[u]) if (v != f) {
    const auto vdp = dfs(v, u);
    fix(dp.first += vdp.second), fix(dp.second += std::min(vdp.first, vdp.second)); }
  if (f) { p[u].f = &p[f]; }
  p[u].val[0] = dp.first, p[u].val[1] = dp.second;
  return dp; }

Scanner sc(fopen("defense.in", "r"));

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); sc.next(trash);
  for (int i=1; i<=n; ++i) w[i] = sc.n();
  for (int i=1; i<n; ++i) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  FILE *out = fopen("defense.out", "w");
  dfs(1, 0);
  for (int i=0; i<m; ++i) {
    int a=sc.n(), x=sc.n(), b=sc.n(), y=sc.n();
    long da = x ? -inf2 : inf2, db = y ? -inf2 : inf2;
    p[a].modify(da); long ans = p[b].modify(db);
    if (da < 0) { ans -= da; } if (db < 0) { ans -= db; }
    fprintf(out, "%lld\n", ans >= inf2 ? -1 : ans);
    p[a].modify(-da), p[b].modify(-db); }
  fclose(out);
}
