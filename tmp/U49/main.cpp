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
#define int long long

/** My code begins here **/

constexpr int N = 500005;
int p[N], pd[N], w[N], wp[N], n, t;

void preInit() {  }
void init() {
  n = sc.n(); t = sc.nl() / 2;
  for (int i = 0; i < n; i++) p[i] = sc.n();
  for (int i = 0; i < n; ++i) pd[i] = p[n - 1] - p[n - i - 1];
  for (int i = 1; i <= n; i++) w[i] = sc.n(); 
  for (int i = 1; i <= n; ++i) wp[i] = wp[i - 1] + w[n - i + 1];
  for (int i = 1; i <= n; ++i) w[i] += w[i - 1];
}

void solve() {
  int l = 0, r = 5000000001;
  while (r - l > 1) {
    int mid = (l + r) / 2, t = 4e18, v = 0;
    for (int s = 0, e = 0, m = 0; s < n; ++s) {
      while (e < n && w[e] - w[s] < mid) v += (w[e + 1] - w[e]) * (p[e] - p[m]), e++;
      while (m < e - 1 && w[m + 1] - w[s] <= mid / 2) v += (w[m + 1] * 2 - w[s] - w[e]) * (p[m + 1] - p[m]), m++;
      if (w[e] - w[s] >= mid) t = std::min(t, v - (w[e] - w[s] - mid) * (p[e - 1] - p[m]) );
      v -= (w[s + 1] - w[s]) * (p[m] - p[s]); }
    v = 0;
    for (int s = 0, e = 0, m = 0; s < n; ++s) {
      while (e < n && wp[e] - wp[s] < mid) v += (wp[e + 1] - wp[e]) * (pd[e] - pd[m]), e++;
      while (m < e - 1 && wp[m + 1] - wp[s] <= mid / 2) v += (wp[m + 1] * 2 - wp[s] - wp[e]) * (pd[m + 1] - pd[m]), m++;
      if (wp[e] - wp[s] >= mid) t = std::min (t, v - (wp[e] - wp[s] - mid) * (pd[e - 1] - pd[m]) );
      v -= (wp[s + 1] - wp[s]) * (pd[m] - pd[s]); }
    if (t <= ::t) l = mid;
    else r = mid; }
  printf ("%lld\n", l); }
