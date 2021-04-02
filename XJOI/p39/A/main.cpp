#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
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

constexpr int N = 5005;
Temps::Vector<int> e[N];
int n, k;

bool ok = true;
bool dp(int u, int f) {
  bool used = false;
  for (int v: e[u]) if (v != f) {
    if (!dp(v,u)) {
      if (used) { ok = false; return false; }
      else { used = true; } } }
  return used; }

void preInit() { } void init() {
  n = sc.n(); k = sc.n();
  for (int i=1;i<n;++i) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  if (n % 2 == 1) { puts("Alan"); return; }
  if ((n-2) / 2 > k) { puts("Alan"); return; }
  if (dp(1,0) && ok) { puts("Bob"); }
  else { puts("Alan"); }
}
