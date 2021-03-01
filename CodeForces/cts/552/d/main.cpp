#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"

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

#define in :
/** My code begins here **/

typedef std::pair<int,int> Point;
typedef std::pair<int,int> Vector;

Vector make_Vector(const Point& a, const Point& b) {
  return Vector{b.first - a.first, b.second - a.second}; }
Vector unify(const Vector& v) {
  int g = std::__gcd(v.first, v.second);
  return Vector({v.first / g, v.second / g}); }

std::vector<Point> p;
int n;

void preInit() { } void init() {
  n = sc.n(); p.resize(n);
  for (int i in range(n)) { int x=sc.nextInt(), y=sc.nextInt(); p[i] = {x,y}; }
} void solve() {
  long long ans = 1ll * n * (n-1) * (n-2);
  for (const auto& a: p) {
    std::map<Vector, int> vs;
    for (const auto& b: p) if (a != b) {
      const auto v = unify(make_Vector(a,b));
      ans -= 2 * vs[v]++; } }
  see(ans);
  printf("%lld\n", ans / 6);
}
