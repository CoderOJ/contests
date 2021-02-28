#include "/home/jack/code/creats/gpl.h"

#define SCANNER_H_CUSTOM
#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/geometry/main.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>
#define in :

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
// #define int long long

/** My code begins here **/

using namespace Temps;
std::vector<Point> p;

bool check(const std::vector<int>& a) {
  std::vector<Segment> segs;
  for (std::size_t i=1; i+1<a.size(); ++i) {
    Segment pos(p[a[i]], p[a[i+1]]);
    for (const auto& pre: segs) { 
      if (pre.isCross_open(pos)) { return false; } }
    segs.push_back(Segment(p[a[i-1]], p[a[i]])); }
  return true; }

int main(int argc, char *const *const argv) {
  assert(argc >= 2);
  Scanner inf(fopen("in", "r"));
  Scanner anf(fopen(argv[1], "r"));
  int T = inf.n();
  for ([[maybe_unused]] int i in range(T)) {
    int n = inf.n(); p.clear(); p.resize(n);
    for (int i in range(n)) { double x=inf.nextInt(), y=inf.nextInt(); p[i]=Point{x,y}; }
    std::vector<int> ans(n);
    for (int i in range(n)) { ans[i] = anf.n() - 1; }
    if (!check(ans)) { return 1; } }
  return 0;
}
