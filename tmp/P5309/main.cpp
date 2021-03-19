#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 1000000007;
constexpr int N = 200005;
constexpr int B = 305;
constexpr int CONC = 455;

using Int = Temps::Intm<Temps::ConstModuler<MOD>>;

struct Block {
  Int a[B], sum=0;
  int l, r;

  void init(int l, int r) {
    this->l = l; this->r = r; }
  void single_modify(int pos, Int del) {
    a[pos - l] += del; sum += del; }

  Int block_query() {
    return sum; }
  Int inter_query(int begin, int end) {
    begin -= l; end -= l; Int ans;
    for (int i: range(begin, end)) {
      ans += a[i]; }
    return ans; }
} b[N / B + 5];
Int add[CONC][CONC];

Int add_query(int end) {
  Int res = 0;
  for (int i: range(1,CONC)) {
    res += Int(end / i) * add[i][i] + add[i][end % i]; }
  return res; }

int bel[N];
int n, m, bn;

void preInit() { } void init() {
  n = sc.n() + 1; m = sc.n();
  bn = (n + B - 1) / B;
  for (int i: range(bn)) { b[i].init(i*B,i*B+B); }
  for (int i: range(n)) { bel[i] = i / B; }
  for (int i: range(1,n)) { b[bel[i]].single_modify(i, sc.n()); }
} void solve() {
  while (m--) {
    int opt = sc.n();
    if (opt == 1) {
      int x=sc.n(), y=sc.n(), z=sc.n();
      if (y == x) { y = 0; }
      if (x >= CONC) {
        for (int i=y; i<n; i+=x) {
          b[bel[i]].single_modify(i,z); } }
      else { for (int i: range(y+1, x+1)) { add[x][i] += z; } } }
    else {
      int l=sc.n(), r=sc.n() + 1;
      Int ans = add_query(r) - add_query(l);
      for (int i: range(bn)) {
        if (b[i].l >= r || b[i].r <= l) { continue; }
        see(b[i].block_query());
        if (b[i].l >= l && b[i].r <= r) { ans += b[i].block_query(); }
        else { ans += b[i].inter_query(std::max(l,b[i].l), std::min(r,b[i].r)); } }
      std::cout << ans << std::endl; } }
}
