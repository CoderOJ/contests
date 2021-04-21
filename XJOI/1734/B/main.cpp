#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

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

constexpr int N = 100000005;
constexpr int M = 5761455;
constexpr int ISP = 1 << 30;
constexpr int ISS = 1 << 31;
constexpr int ISL = ISP - 1;
int primes[M], *primes_top=primes;
unsigned int least[N];
int n;

void preInit() { } void init() {
  n = sc.n();
} void solve() {
  least[1] = 1, least[2] = 1; 
  *primes_top++ = 2;
  least[4] = 2 | (3 << 30);
  for (int i=3; i<=n; ++i) {
    if (!(least[i] & ISP)) {
      *primes_top++ = i;
      least[i] = i | ISS; }
    for (int *_j=primes; _j<primes_top; ++_j) {
      const int j = *_j, k = i * j;
      if (k > n) break;
      if (i % j == 0) {
        const int li = least[i] & ISL;
        least[k] = ((least[i] & ISS) ? li : j * li) | ((least[i]&ISS)^ISS) | ISP;
        break; }
      else {
        const int li = least[i] & ISL, lj = least[j] & ISL;
        least[k] = li * lj | (least[j] & ISS) | ISP; } } }
  long long ans = 0;
  for (int i=1; i<=n; ++i) {
    int li = least[i] & ISL;
    ans += n / li - (i-1) / li; }
  printf("%lld\n", ans);
}
