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

int n, ans;
std::string s;
std::set< std::string > st;

void test(std::string str) {
  if (st.count(str)) { return; }
  st.insert(str); std::reverse(str.begin(), str.end()); st.insert(str);
  ans ++; }

void append(char c) {
  s.push_back(c); n++;
  std::string cur;
  repb (i,n-1,0) {
    cur.push_back(s[i]);
    test(cur);
    see(cur, ans);
  }
}

void preInit() { } void init() { } void solve() {
  int n=sc.n(), q=sc.n();
  rep (i,n) append(sc.nextChar());
  printf("%d\n", ans);
  while (q--) {
    append(sc.nextChar());
    printf("%d\n", ans); }
}
