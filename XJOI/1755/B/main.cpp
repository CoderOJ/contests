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

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 100005;
int mu[N];

void preInit() {
  mu[1] = 1;
  for (int i=1; i<N; ++i) 
    for (int j=i*2; j<N; j+=i) 
      mu[j] -= mu[i]; } 

long long calc_3(int n) {
  long long res = 0;
  for (int i=1; i*i*i<=n; ++i) {
    for (int j=i+1; j*j*i<=n; ++j) 
      res += (n / (i * j) - j) * 6ll + 3;
    res += (n / (i * i) - i) * 3ll + 1; }
  return res; }

void init() { }
void solve() { 
  int n = sc.n();
  long long ans = 0;
  for (int g = 1; g * g <= n; ++g) if (mu[g] != 0) 
    ans += mu[g] * calc_3(n / (g * g));
  printf("%lld\n", ans); }
