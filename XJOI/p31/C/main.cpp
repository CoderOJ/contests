 #include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/Vector.h"

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

constexpr int N = 85;
constexpr int MOD = 1000000007;
// using Int = Temps::Intm<Temps::ConstModuler<MOD>>;
typedef Temps::Intm<Temps::ConstModuler<MOD>> Int;
Temps::Vector<int> e[N];
int n;

void preInit() { } void init() {
  n = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  if (static_cast<int>(e[1].size()) == n - 1) { std::cout << Int(n * 2 - 3) / Int(n) << std::endl; }
  else { std::cout << Int(n-1) / Int(2) << std::endl; }
}
