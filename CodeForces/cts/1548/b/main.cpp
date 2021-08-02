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


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define int long long

/** My code begins here **/

constexpr int B = 20;
constexpr int N = 200005;
int a[N], n;
int d[N][B];

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i=0; i<n+2; i++) for (int j=0; j<B; j++) d[i][j]=0;
  for (int i=0; i<n; i++) a[i] = sc.nl();
  for (int i=0; i+1<n; i++) d[i][0] = std::abs(a[i] - a[i + 1]);
  for (int i=0; i+1<B; i++)
    for (int j=0; j+(2<<i)<n; j++)
      d[j][i + 1] = Temps::gcd(d[j][i], d[j + (1 << i)][i]);
} 

void solve() 
{
  int ans = 0;
  for (int l=0; l<n-1; l++) {
    int cur_gcd = 0, r = l;
    for (int i=B-1; i>=0; i--) if (d[r][i] && Temps::gcd(d[r][i], cur_gcd) != 1) {
      cur_gcd = Temps::gcd(d[r][i], cur_gcd); r += (1 << i); }
    checkMax(ans, r - l); }
  printf("%lld\n", ans + 1);
}
