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
// #include "/home/jack/code/geometry/main.hpp"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace Temps;
constexpr int N = 100005;
std::pair<int, int> p[N]; int r[N];
long long l;
int n;

void preInit() {  } 
void init() 
{
  int x = sc.nextInt(), y = sc.nextInt(); l = 1ll * sc.nextInt() * sc.nextInt();
  n = sc.n(); 
  for (int i=0; i<n; ++i) p[i].first = sc.nextInt() - x, p[i].second = sc.nextInt() - y, r[i] = sc.n();
} 

void solve() 
{
  auto dis_sq = [](int i) { return 1ll * p[i].first * p[i].first + 1ll * p[i].second * p[i].second; };
  for (int i=0; i<n; ++i) {
    if (dis_sq(i) <= 1ll * r[i] * r[i]) {
      puts("1.00000000000"); return; } }

  std::vector<std::pair<double, int>> arcs;
  auto getarg_abc_a = [](double a, double b, double c) {
    return std::acos((b*b + c*c - a*a) / (2*b*c)); };
  for (int i=0; i<n; ++i) {
    double d = std::sqrt(dis_sq(i));
    if (d > static_cast<double>(r[i] + l)) { continue; }
    double arg_cir = std::atan2(p[i].second, p[i].first), arg_del;
    if (arg_cir < 0) { arg_cir += M_PI*2; }
    if (static_cast<double>(l) > d + static_cast<double>(r[i]) || l * l + 1ll * r[i] * r[i] >= dis_sq(i)) {
      arg_del = std::asin(r[i] / d); }
    else { arg_del = getarg_abc_a(r[i], d, static_cast<double>(l)); }
    double arg_l = arg_cir - arg_del, arg_r = arg_cir + arg_del;
    // see(i, arg_l, arg_r);
    if (arg_r > M_PI*2) { arg_l -= M_PI*2; arg_r -= M_PI*2; }
    if (arg_l < 0) { 
      arcs.emplace_back(arg_l+M_PI*2, 1); arcs.emplace_back(M_PI*2, -1);
      arcs.emplace_back(0, 1); arcs.emplace_back(arg_r, -1); }
    else { arcs.emplace_back(arg_l, 1); arcs.emplace_back(arg_r, -1); } }
  arcs.emplace_back(M_PI*2, 0);
  std::sort(arcs.begin(), arcs.end());
  // see(arcs);
  double ans = 0, last = 0; int cnt = 0;
  for (const auto& [cur, del] : arcs) {
    if (cnt > 0) { ans += cur-last; }
    last = cur; cnt += del; }
  printf("%.11lf\n", ans / (M_PI * 2));
}
