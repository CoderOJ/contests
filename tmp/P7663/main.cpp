#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


constexpr int N = 505;
int up[N][N], down[N][N];
char map[N][N];
int n, m;

template <class T> 
__attribute__((always_inline)) inline
constexpr T sqr(const T& x) { return x * x; }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  for (int i: range(n)) 
    sc.next(map[i]);
} void solve() {

  for (int i: range(n)) for (int j: range(m))
    if (map[i][j] == 'x') up[i][j] = down[i][j] = i;
    else up[i][j] = -1000, down[i][j] = 1000;

  for (int i: range(1,n)) for (int j: range(m))
    checkMax(up[i][j], up[i-1][j]);
  for (int i: range(n-1, 0, -1)) for (int j: range(m))
    checkMin(down[i-1][j], down[i][j]);


  int T = sc.n();
  while (T--)
  {
    int x = sc.n() - 1, y = sc.n() - 1;

    int ans = std::numeric_limits<int>::max();
    for (int i: range(m)) {
      // see(x, y, i, up[x][i], down[x][i]);
      checkMin(ans, sqr(y - i) + sqr(x - up[x][i]));
      checkMin(ans, sqr(y - i) + sqr(x - down[x][i])); }
    printf("%d\n", ans);

    for (int i=0; i<=x; ++i) 
      checkMin(down[i][y], x);
    for (int i=x; i<n; ++i)
      checkMax(up[i][y], x);
  }

}
