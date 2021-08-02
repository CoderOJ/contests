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


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 200005;
int n, m, q;

int higher_cnt[N];
int ans = 0;
  
void add(int u, int v) {
  if (u > v) { std::swap(u, v); }
  if (higher_cnt[u] == 0) ans--;
  higher_cnt[u]++; }
void remove(int u, int v) {
  if (u > v) { std::swap(u, v); }
  higher_cnt[u]--; 
  if (higher_cnt[u] == 0) ans++; }

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n(); ans = n;
  for (int i=0; i<m; i++) add(sc.n(), sc.n());
} 

void solve() 
{
  int q = sc.n();
  for (int i=0; i<q; i++) {
    int opt = sc.n();
    if (opt == 1) { add(sc.n(), sc.n()); }
    else if (opt == 2) { remove(sc.n(), sc.n()); }
    else { printf("%d\n", ans); } }
}
