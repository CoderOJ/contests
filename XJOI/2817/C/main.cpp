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
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 5;
constexpr int W = 10;
constexpr int MOD = 998244353;
using Int = Temps::Intm<MOD>;
Int dp[W * W * W * W * W];
int a[N], b[N], n;

int compress(int a[]) {
  return a[0] + a[1] * 10 + a[2] * 100 + a[3] * 1000 + a[4] * 100000; }
void decompress(int a[], int v) {
  a[0] = v % 10; v /= 10;
  a[1] = v % 10; v /= 10;
  a[2] = v % 10; v /= 10;
  a[3] = v % 10; v /= 10;
  a[4] = v % 10; v /= 10; }

void preInit() { } 
void init() 
{
   n = sc.n();
   for (int i=0; i<n; i++) a[i] = sc.n() - 1;
   for (int i=0; i<n; i++) b[i] = sc.n() - 1;
   dp[compress(a)] = 1;
} 

inline bool ok(int a[]) {
  for (int i=0; i<n; i++) 
    for (int j=i+1; j<n; j++) 
      if (a[i] == a[j])
        return false;
  return true; }

void solve() 
{
  int lim = compress(b);
  for (int mask=0; mask<=lim; mask++) {
    decompress(a, mask);
    if (!ok(a)) continue;
    for (int i=0; i<n; i++) for (int j=i+1; j<n; j++) {
      a[i]++; a[j]++;
      if (ok(a)) dp[compress(a)] += dp[mask]; 
      a[i]--; a[j]--; } }
  std::cout << dp[lim] << std::endl; }
