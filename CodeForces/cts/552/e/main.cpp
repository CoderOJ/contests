#include "/home/jack/code/creats/gpl.h"

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
#define int long long

/** My code begins here **/

constexpr int N = 6005;
int i, j, n, x, y, m, k, ans, a[N], b[N];

std::vector <int> f;
std::string s, t;
std::pair<int, int> solve(int l, int r) {
  int x = 0, y = a[l];
  for (int i = l; i < r; i++)
    if (b[i] == 1) x += y, y = a[i + 1];
    else y *= a[i + 1];
  return std::make_pair(x, y); }

void preInit() {} void init() {
  std::cin >> s; t = "1*"; t.append(s); t.append("*1");
  s = t; n = s.size(); m = n / 2;
  for (i = 0; i < n; i += 2) a[i / 2] = s[i] - '0';
  for (i = 1; i < n; i += 2)
    if (s[i] == '+') b[i / 2] = 1;
    else { b[i / 2] = 2; f.push_back(i / 2); }
} void solve() {
  int max = 0;
  for (i = 0; i < f.size(); i++)
    for (j = i + 1; j < f.size(); j++) {
      std::pair<int,int> tmp = solve(0, f[i]);
      x = tmp.first, y = tmp.second;
      tmp = solve(f[i] + 1, f[j]);
      y *= tmp.first + tmp.second;
      int xx = a[f[j]];
      a[f[j]] = y;
      tmp = solve(f[j], m);
      checkMax(max, x + tmp.first + tmp.second);
      a[f[j]] = xx; }
  printf("%lld\n", max); }
