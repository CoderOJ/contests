#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

const int MOD = 1000000007;
typedef Intm::Intm<MOD> Int;
const int N = 1048576;
int n, l, r;

int get_2(int u) {
  int res = 0;
  while (u) {
    res++; u >>= 1; }
  return res; }

void fwt(Int a[], int n) {
  for (int l=1; l<n; l<<=1) {
    for (int i=0; i<n; i+=2*l) {
      for (int j=0; j<l; ++j) {
        int x=i+j, y=i+l+j;
        Int u=a[x], v=a[y];
        a[x] = (u+v);
        a[y] = (u-v);
} } } } 

Int a[N];
void preInit() { } void init() { } void solve() { 
  n = sc.nlm(MOD-1); l = sc.n(); r = sc.n();
  int m = 1 << get_2(r);
  repi (i,l,r) a[i] = 1;
  fwt(a,m);
  rep (i,m) a[i] = a[i].pow(n);
  fwt(a,m);
  printf("%u", static_cast<unsigned>(a[0] / Int(m)));
}
