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

const int N = 300005;
int a[N], b[N], n, m;

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n) { a[i] = sc.n(); b[i] = sc.n(); }
}

typedef std::pair<int, int> Ob;
struct Dr {
  long long ans;
  int sz;
  std::multiset<Ob, std::greater<Ob>> single;
  struct cmpSum {
    bool operator() (Ob a, Ob b) const {
      int sa = a.first + a.second;
      int sb = b.first + b.second;
      return sa > sb; } };
  std::multiset<Ob, cmpSum> multi;
  int top() { 
    if (single.size() < 1) { return -0x3f3f3f3f; }
    return single.begin()->first; }
  int top2_single() {
    if (single.size() < 2) { return -0x3f3f3f3f; }
    return single.begin()->first + (++single.begin())->first; }
  int top2_multi() {
    if (multi.size() < 1) { return -0x3f3f3f3f; }
    return multi.begin()->first + multi.begin()->second; }
  int top2() { return std::max(top2_single(), top2_multi()); } 
  void pop() {
    auto top = *single.begin(); single.erase(single.begin());
    ans -= top.first; sz--;
    if (top.second != -1) {
      auto tr = multi.find(Ob(top.first, top.second));
      multi.erase(tr);
      single.insert(Ob(top.second, -1)); } }
  void pop2() {
    int t1 = top2_single();
    int t2 = top2_multi();
    if (t1 > t2) { pop(); pop(); }
    else {
      auto top = *multi.begin(); multi.erase(multi.begin());
      sz -= 2; ans -= top.first + top.second;
      single.erase(single.find( Ob(top.first,top.second) )); } }
  void push(Ob a) {
    // see("push", a.first, a.second);
    if (a.second == -1) { ans += a.first; sz++; single.insert(a); }
    else { ans += a.first + a.second; sz+=2; single.insert(a); multi.insert(a); } }
} st;

void solve()
{
  rep (i,n) { st.push(Ob(b[i]-a[i], a[i])); }
  while (st.sz - m >= 2) { st.pop2(); }
  while (st.sz - m >= 1) { st.pop(); }
  printf("%lld\n", st.ans);
}
