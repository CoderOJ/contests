#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#define GEOMETRY_H_EPS 1e-12
#include "/home/jack/code/geometry/main.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

using namespace Temps;
constexpr int N = 505;
Point p[N];
Vector v[N];
int n;

bool check(const std::vector<int>& a) {
  std::vector<Segment> segs;
  for (std::size_t i=1; i+1<a.size(); ++i) {
    Segment pos(p[a[i]], p[a[i+1]]);
    for (const auto& pre: segs) { 
      if (pre.isCross_open(pos)) { return false; } }
    segs.push_back(Segment(p[a[i-1]], p[a[i]])); }
  return true; }

template <typename T> std::vector<T>
add(const std::vector<T>& a, const std::vector<T>& b, const std::vector<T>& c) {
  std::vector<T> res; res.reserve(a.size() + b.size() + c.size());
  for (const T& i: a) { res.push_back(i); }
  for (const T& i: b) { res.push_back(i); }
  for (const T& i: c) { res.push_back(i); }
  return res; }

template <typename T> std::vector<T>
rev(std::vector<T> a) {
  std::reverse(a.begin(), a.end());
  return a; }

void preInit() { } void init() {
  n = sc.n();
  rep (i,n) { double x=sc.nextInt(), y=sc.nextInt(); p[i] = Point{x,y}; }
  rep (i,n) { v[i] = Vector(p[0], p[i]); }
  double arg = v[n-1].arg();
  rep (i,n) v[i] = v[i].rotate(-arg);
  rep (i,n) p[i] = p[0].add(v[i]);
} void solve() {
  std::vector<int> le, mid, ri;
  repa (i,n-2) {
    if (p[i].x < p[0].x) { le.push_back(i); }
    else if (p[i].x < p[n-1].x) { mid.push_back(i); }
    else { ri.push_back(i); } }

  std::sort(le.begin(), le.end(), [](int x, int y) {
    return Vector(p[0],p[x]).cross(Vector(p[0],p[y])) < 0; });
  std::sort(mid.begin(), mid.end(), [](int x, int y) {
    return p[x].x < p[y].x; });
  std::sort(ri.begin(), ri.end(), [](int x, int y) {
    return Vector(p[n-1],p[x]).cross(Vector(p[n-1],p[y])) < 0; });

  auto a0 = add({0}, add(le, mid, ri), {n-1});
  auto a1 = add({0}, add(le, mid, rev(ri)), {n-1});
  auto a2 = add({0}, add(rev(le), mid, ri), {n-1});
  auto a3 = add({0}, add(rev(le), mid, rev(ri)), {n-1});

  std::vector<int> ans;
  if (check(a0)) { ans = std::move(a0); }
  else if (check(a1)) { ans = std::move(a1); }
  else if (check(a2)) { ans = std::move(a2); }
  else { ans = std::move(a3); }

  for (int i: ans) { printf("%d ", i + 1); } puts("");
}
