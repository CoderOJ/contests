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

constexpr int N = 100005;
// template <class T> using Vector = std::vector<T>;

constexpr int mod = 1000000007;
int n, m, num[10], tot, res[N * 20];
Vector<int> v[N * 20][10];
std::queue<Vector<int>> q;

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); 
  tot = n; memset (res, -1, sizeof (res) );
} void solve() {
  for (int i = 1, x, y; i <= m; i++) {
    x = sc.n(), y = sc.n();
    int tmp = i, sz = 0;
    while (tmp) num[++sz] = tmp % 10, tmp /= 10;
    if (sz == 1) v[x][num[sz]].push_back (y);
    else v[x][num[sz]].push_back (tot + 1), v[tot + sz - 1][num[1]].push_back (y);
    for (int j = 2; j < sz; j++) v[tot + j - 1][num[sz - j + 1]].push_back (tot + j);

    if (sz == 1) v[y][num[sz]].push_back (x);
    else v[y][num[sz]].push_back (tot + sz - 1), v[tot + 1][num[1]].push_back (x);
    for (int j = 2; j < sz; j++) 
      v[tot + sz - j + 1][num[sz - j + 1]].push_back (tot + sz - j);
    tot += sz; }

  q.push({1}), res[1] = 0;
  while (!q.empty() ) {
    const Vector<int> x = q.front(); q.pop();
    see(x);
    for (int i = 0; i < 10; i++) {
      Vector<int> y;
      for (unsigned int j = 0; j < x.size(); j++) 
        for (unsigned k = 0; k < v[x[j]][i].size(); k++) 
          if (res[v[x[j]][i][k]] == -1) {
            res[v[x[j]][i][k]] = (10ll * res[x[j]] + i) % mod; y.push_back (v[x[j]][i][k]); }
      if (!y.empty() ) q.push (y); } }
  for (int i = 2; i <= n; i++) printf ("%d\n", res[i]); }
