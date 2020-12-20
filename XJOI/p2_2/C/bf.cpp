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

constexpr int N = 50005;
constexpr int MOD = 323232323;
std::map<int, int> mp;
int n,m,q;

typedef int uint16;
struct Inter { uint16 l,r; int mul, add; } inter[N];
int traceId[N * 2];

void preInit() { } void init() {
  sc.n(); n = sc.n(); m = sc.n(); q = sc.n();
} void solve() {
  int placement_cnt = 1;
  repa (cs, q) {
    char opt = sc.nextChar();
    if (opt == 'I') {
      uint16 l=sc.n(), r=sc.n(), y=sc.n();
      int p=sc.n(), q=sc.n();
      inter[y] = {l,r, p, q}; 
      traceId[placement_cnt++] = y; }
    else if (opt == 'D') {
      int id = sc.n(), y = traceId[id]; 
      inter[y] = {0, 0, 1, 0}; }
    else {
      uint16 x=sc.n(), l=sc.n(), r=sc.n();
      long long ans = 0;
      Inter pos;
      Inter* pos_ptr = inter + l;
      Inter* pos_ptr_end = inter + r + 1;
      for (;pos_ptr+3 < pos_ptr_end; pos_ptr += 4) {
        pos = *pos_ptr; 
        if (x >= pos.l && x <= pos.r) {
          ans *= pos.mul; ans += pos.add; ans %= MOD; } 
        pos = *(pos_ptr+1);
        if (x >= pos.l && x <= pos.r) {
          ans *= pos.mul; ans += pos.add; ans %= MOD; } 
        pos = *(pos_ptr+2);
        if (x >= pos.l && x <= pos.r) {
          ans *= pos.mul; ans += pos.add; ans %= MOD; } 
        pos = *(pos_ptr+3);
        if (x >= pos.l && x <= pos.r) {
          ans *= pos.mul; ans += pos.add; ans %= MOD; } 
      }
      for (;pos_ptr < pos_ptr_end;pos_ptr++) {
        pos = *pos_ptr; 
        if (x >= pos.l && x <= pos.r) {
          ans *= pos.mul; ans += pos.add; ans %= MOD; } 
      }
      printf("%lld\n", ans); } }
}
