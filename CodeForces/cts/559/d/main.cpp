#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"

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

constexpr int N = 100005;
double pow_2[N];
int x[N], y[N];
int n;

void preInit() { 
  pow_2[0] = 1;
  for (int i: range(1,N)) { pow_2[i] = pow_2[i-1] / 2; } } 
void init() {
  n = sc.n();
  for (int i: range(n)) { x[i] = sc.nextInt(); y[i] = sc.nextInt(); }
} void solve() {
  double ans = 0;
  for (int i: range(n)) {
    for (int j=(i+1)%n, k=60, p=2; k && i != j; k--, j=(j+1)%n, p++) {
      ans += (pow_2[p] - pow_2[n]) * 
             ( 1.0 * x[i] * y[j] - 1.0 * x[j] * y[i] -
               Temps::gcd(std::abs(x[i] - x[j]), std::abs(y[i] - y[j]))); } }
	ans = ans / 2 / (1 - pow_2[n]*(1 + n + 1.0*n*(n-1)/2)) + 1;
  printf("%.10lf\n", ans);
}
