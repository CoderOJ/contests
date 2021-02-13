#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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

/** My code begins here **/

typedef std::pair<int, int> Point;
constexpr int N = 2005;
int map[N][N], n, rev, bx, by, best;
int id[N * N];

int at(int x, int y) {
  if (x < 1 || x > n || y < 1 || y > n) { 
    return std::numeric_limits<int>::min(); }
  if (rev) { std::swap(x, y); }
  if (map[x][y] != -1) { return map[x][y]; }
  printf("? %d %d\n", x, y); std::fflush(stdout);
  int cur; scanf("%d", &map[x][y]); cur = map[x][y];
  if (rev) { std::swap(x, y); }
  if (checkMax(best, cur)) { bx = x; by = y; }
  return cur; }

void preInit() { } void init() {
  memset(map, -1, sizeof(map));
  scanf("%d", &n);
} void solve() {
  int l=1, r=n, d=1, u=n;
  while (true) {
    int mid = (l + r) / 2;

    repi (i,d,u) at(mid, i);
    repi (dx,-1,1) repi (dy,-1,1) {
      at(bx + dx, by + dy); }

    if (bx > mid) { l = mid + 1; }
    else { r = mid - 1; }

    if (l > r) { break; }
    std::swap(l, d); std::swap(r,u); std::swap(bx, by); rev ^= 1;
  }
  if (rev) { std::swap(bx, by); }
  printf("! %d %d\n", bx, by);
}
