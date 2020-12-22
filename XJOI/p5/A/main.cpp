#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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
// #define int long long

/** My code begins here **/

#define long long long

bool calc(int n, int p) {
  int k = 0, res = 1;
  while (res && n > k*k) {
    res *= (n-k*k); res %= p; k++; }
  return !res; }

int calc_loop_prim(int p, int q) {
  int res = p/2+1; q--;
  while (q) { res*=p; q--; }
  return res; }

int calc_loop(int n) {
  int res = 1;
  for (int i=2; i*i<=n; ++i) {
    if (n%i == 0) {
      int cnt=0;
      while (n%i==0) { n/=i; cnt++; }
      res *= calc_loop_prim(i,cnt); } }
  if (n != 1) { res *= calc_loop_prim(n, 1); }
  return res; }

long count(long n, long p) {
  long ans = 0;
  int id = 1;
  while (id<=n) {
    ans += calc(id, p); id++;
    if (id>p*p && (n-id+1)%p == 0) break; }
  ans += calc_loop(p) * ((n-id+1) / p);
  see(n,id,p,ans);
  return ans; }

void preInit() { } void init() { } void solve() {
  long l=sc.nl(), r=sc.nl(), p=sc.nl();
  printf("%lld\n", count(r,p) - count(l-1,p));
}
