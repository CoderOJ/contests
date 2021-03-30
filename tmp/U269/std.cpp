#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
#include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


void preInit() { } void init() {

} void solve() {
  Polys::Poly a(8), b(8);
  a[0] = 1; a[1] = 2; a[2] = 1;
  b[0] = 1; b[1] = 1;
  a.dft();
  b.dft();
  logArray(a.a, a.a+8);
  logArray(b.a, b.a+8);
  for (int i=0; i<8; i++) a[i] *= b[i];
  logArray(a.a, a.a+8);
  std::reverse(a.a+1, a.a+8);
  logArray(a.a, a.a+8);
  a.dft();
  logArray(a.a, a.a+8);
  for (int i=0; i<8; i++) a[i] /= 8;
  logArray(a.a, a.a+8);
}
