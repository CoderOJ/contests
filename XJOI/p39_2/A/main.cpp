#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
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

constexpr int S = 200, d = 1000000000;
constexpr int sp = d / S + 1;
Temps::Vector < int > id[S + 10][S + 10];
struct Vector {
  int x, y; };
inline Vector operator + (Vector a, Vector b) {
  return {a.x + b.x, a.y + b.y }; }
inline Vector operator - (Vector a, Vector b) {
  return {a.x - b.x, a.y - b.y }; }
inline long long operator * (Vector a, Vector b) {
  return 1ll * a.x * b.x + 1ll * a.y * b.y; }
inline long long operator ^ (Vector a, Vector b) {
  return 1ll * a.x * b.y - 1ll * a.y * b.x; }
int n, q;

struct Line {
  Vector s, t; } a[100010];
inline int check(Line a, Vector b) {
  return ((a.t - a.s) ^ (b - a.s)) == 0; }
inline long long calc(Line a, int x) {
  return (1ll * (x - a.s.x) * a.t.y + 1ll * (a.t.x - x) * a.s.y) /
    (a.t.x - a.s.x); }

void preInit() {}

void init() {
  n = sc.n(); q = sc.n();
  for (int i = 1; i <= n; i++) {
    Vector x, y;
    x.x = sc.n(); x.y = sc.n(); y.x = sc.n(); y.y = sc.n();
    a[i] = {x, y };
    if (x.x == y.x) { for (int j = 0; j < S; j++) id[x.x / sp][j].push_back(i); }
    else {
      long long lst = calc(a[i], 0);
      for (int j = 0; j < S; j++) {
        long long cur = calc(a[i], (j + 1) * sp);
        long long l = std::min(lst, cur) / sp, r = std::max(lst, cur) / sp;
        if (l > r) std::swap(l, r);
        l = std::max(l, 0ll); r = std::min(r, S - 1ll);
        for (int k = l; k <= r; k++) { id[j][k].push_back(i); }
        lst = cur; } } } }

void solve() {
  for (int i = 1; i <= q; i++) {
    Vector cur; cur.x = sc.n(); cur.y = sc.n();
    int ans = 0;
    int idx = cur.x / sp, idy = cur.y / sp;
    for (auto i : id[idx][idy]) ans += check(a[i], cur);
    printf("%d\n", ans); } }
