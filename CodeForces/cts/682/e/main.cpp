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

constexpr int N = 5005;
using Point = std::pair<int,int>;
Point a[N]; int n;

void preInit() {  } 
void init() {
  n = sc.n(); sc.n();
  for (int i=0; i<n; ++i)
    a[i].first = sc.nextInt(), a[i].second = sc.nextInt(); } 

long long area(Point a, Point b, Point c) { b = b - a, c = c - a;
  return std::abs(1ll * b.first * c.second - 1ll * b.second * c.first); }

void solve() 
{
  std::shuffle(a, a + n, std::mt19937(20050610));
  Point x=a[0], y=a[1], z=a[2];
  bool is_largest;
  do { is_largest = true;
    for (int i=0; i<n; ++i) {
      if (area(x,y,a[i]) > area(x,y,z)) { is_largest = false; z = a[i]; }
      if (area(x,a[i],z) > area(x,y,z)) { is_largest = false; y = a[i]; }
      if (area(a[i],y,z) > area(x,y,z)) { is_largest = false; x = a[i]; } } } 
  while (!is_largest);
  Point ax = y + z - x;
  Point ay = x + z - y;
  Point az = x + y - z;
  printf("%d %d\n", ax.first, ax.second);
  printf("%d %d\n", ay.first, ay.second);
  printf("%d %d\n", az.first, az.second);
}
