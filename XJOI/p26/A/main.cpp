#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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


template <class T1, class T2> 
T1 exchange(T1& a, T2&& b) {
  T1 back = a; a = b; return back; }

constexpr int N = 200005;
constexpr int M = 75;
using Mask = std::bitset<M>;

struct Row {
  int bit[N];
  int a, b;
};

int n, m;
Row row[M];
Temps::Vector<int> rid;
Mask mask[N];

bool row_cmp(const Row& a, const Row& b) {
  return a.b != b.b ? a.b > b.b : a.a > b.a; }

struct LinearBasis {
  Mask a[M], use;
  void insert(Mask p) {
    rep (i,m) if (p[i]) {
      if (!a[i].any()) { a[i] = p; break; }
      else { p ^= a[i]; } } }
  Mask get(Mask p) {
    rep (i,m) if (p[i] && a[i].any()) { p ^= a[i]; }
    return p; }
  void minimize() {
    rep (i,m) if (a[i].any()) {
      a[i] = get(exchange(a[i], 0)); } }
  inline bool can_set_to(int pos, bool val) {
    return use[pos]==val || a[pos].any(); }
  inline void set_pos(int pos, bool val) {
    if (use[pos] != val) { use ^= a[pos]; } }
} lb;

long long pow3(long long x) {
  long long res = 1;
  rep (i,x) { res *= 3; }
  return res; }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n) rep (j,m) row[j].bit[i] = sc.nextChar() - '0';
  rep (i,m) { row[i].a = sc.nextInt(); row[i].b = sc.n(); }
  std::sort(row, row+m, row_cmp);
  rep (i,n) rep (j,m) { mask[i][j] = row[j].bit[i]; }
} void solve() {
  rep (i,n) lb.insert(mask[i]); lb.minimize();
  // rep (i,m) see(lb.a[i]);
  int pos = 0;
  while (pos < m) {
    bool have_next = pos+1 < m && row[pos].b == row[pos+1].b;
    // see(pos, have_next, row[pos].a, row[pos].b);
    // see(lb.use);
    if (have_next) {
      // see(lb.can_set_to(pos,1));
      if (lb.use[pos+1]) {
        lb.set_pos(pos, 1); lb.set_pos(pos+1,0); }
      else {
        if (lb.a[pos][pos+1]) { 
          if (lb.a[pos+1].any()) {
            lb.set_pos(pos,1); lb.set_pos(pos+1,0); }
          else {
            auto anothor = exchange(lb.a[pos],0);
            anothor[pos]=0; anothor[pos+1]=0;
            lb.insert(anothor); lb.minimize(); } }
        else {
          lb.set_pos(pos, 1); lb.set_pos(pos+1,0); } } 
      pos += 2; }
    else {
      lb.set_pos(pos, row[pos].a == 1);
      pos += 1; } }
  long long ans = 0;
  rep (i,m) if (lb.use[i]) { ans += row[i].a * pow3(row[i].b); }
  printf("%lld\n", ans);
}
