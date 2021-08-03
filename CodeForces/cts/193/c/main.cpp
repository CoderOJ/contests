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

int n[4][4];
int a,b,c,d,e,f;
void preInit() {  } 
void init() 
{
  n[0][1] = a = sc.n(); n[0][2] = b = sc.n(); n[0][3] = c = sc.n();
  n[1][2] = d = sc.n(); n[1][3] = e = sc.n(); 
  n[2][3] = f = sc.n();
} 

#define rep(i,n) for (int i=0;i<n;i++)

void out(std::initializer_list<int> a) {
  char c = 'a';
  for (int x: a) { 
    rep (i,x) putchar(c);
    c = c == 'a' ? 'b' : 'a'; } 
  puts(""); }

void valid(std::initializer_list<int> _a) {
  Vector a = _a; std::sort(a.begin(), a.end());
  if (std::accumulate(a.begin(), a.end(), 0) % 2) { puts("-1"); exit(0); }
  if (std::accumulate(a.begin(), a.end() - 1, 0) < a.back()) { puts("-1"); exit(0); } }

void solve() 
{
  rep (a,4) rep (b,4) rep (c,4) if (a < b && b < c)
    valid({n[a][b], n[a][c], n[b][c]});
  valid({n[0][1], n[1][2], n[2][3], n[0][3]});

  int t[7] = {0};
  t[0] = 0;
  t[1] = (e + f - a - b) >> 1;
  t[2] = (d + f - a - c) >> 1;
  t[3] = (b + c - f) >> 1;
  t[4] = (d + e - b - c) >> 1;
  t[5] = (a + c - e) >> 1;
  t[6] = (a + b - d) >> 1;
  while (std::any_of(t, t+7, [](int x) { return x < 0; }) && t[0] <= std::min({a,b,c})) { t[0]++;
    t[1]++; t[2]++; t[3]--;
    t[4]++; t[5]--; t[6]--; }

  int len = (d + e + f) / 2 + t[0]; printf("%d\n", len);
  out({len});
  out({t[1] + t[2] + t[3], t[0] + t[4] + t[5] + t[6]});
  out({t[1], t[2] + t[3], t[4] + t[5], t[6] + t[0]});
  out({0, t[1], t[2], t[3], t[4], t[5], t[6], t[0]});
}
