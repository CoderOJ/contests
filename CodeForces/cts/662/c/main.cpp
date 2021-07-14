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

constexpr int N = 20;
constexpr int L = 1 << N;
long long a[L], cnt[L], w[L], n, m, l;

void fwt(long long *a) {
  for (int i=0; i<n; ++i) {
    for (int j=0; j<l; ++j) if (j & (1 << i)) {
      long long x = a[j ^ (1 << i)], y = a[j];
      a[j ^ (1 << i)] = x + y; a[j] = x - y; } } }
void ifwt(long long *a) {
  for (int i=0; i<n; ++i) {
    for (int j=0; j<l; ++j) if (j & (1 << i)) {
      long long x = a[j ^ (1 << i)], y = a[j];
      a[j ^ (1 << i)] = (x + y) / 2; a[j] = (x - y) / 2; } } }

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n();
  for (int i=0; i<n; ++i) 
    for (int j=0; j<m; ++j) 
      a[j] |= (sc.nextChar() == '1') << i;
  l = 1 << n;
} 

void solve() 
{
  for (int i=0; i<m; ++i) 
    cnt[a[i]]++;
  for (int i=0; i<l; ++i) {
    w[i] = __builtin_popcount(static_cast<unsigned>(i));
    w[i] = std::min(w[i], n - w[i]); }
  fwt(w); fwt(cnt);
  for (int i=0; i<l; ++i)
    w[i] *= cnt[i];
  ifwt(w);
  std::cout << *std::min_element(w, w + l) << std::endl;
}
