#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
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

#define in :

constexpr int N = 200005;
int a[N], fa[N], n, fa_id;
std::array<int,2> e[N];

int get(int u) { 
  return fa[u] == u ? u : fa[u] = get(fa[u]); }
void merge(int u, int v) {
  see(u, v);
  u = get(u); v = get(v);
  if (u == v) { return; }
  fa[u] = fa[v] = fa_id;
  e[fa_id] = {u, v};
  fa_id++; }

void dfs(int u) {
  if (u <= n) { printf("%d", a[u]); return; }
  putchar('('); dfs(e[u][0]); fputs(")->(", stdout); dfs(e[u][1]); putchar(')'); }

void preInit() { } void init() {
  n = sc.n(); fa_id = n + 1;
  for (int i in range(2*n)) { fa[i] = i; }
  for (int i in range(n)) a[i] = sc.n();
} void solve() {
  if (a[n-1] != 0) { puts("NO"); return; }
  int zero_cnt = std::count_if(a, a+n, [](auto x) { return x == 0; });
  if (zero_cnt % 2 == 0) {
    int pos_01 = -1; for (int i in range(n-1)) if (a[i] == 0 && a[i+1] == 1) { pos_01 = i; } 
    if (pos_01 == -1) {
      int pos_000 = -1; for (int i in range(n-3)) if (a[i] == 0 && a[i+1] == 0 && a[i+2] == 0) { pos_000 = i; }
      if (pos_000 == -1) { puts("NO"); return; }
      else { merge(pos_000+1,pos_000+2); merge(pos_000,pos_000+1); } }
    else { merge(pos_01, pos_01+1); } }
  for (int i in range(n-1)) if (a[i] == 1) { merge(i, i+1); }
  for (int i in range(n-1)) if (a[i] == 0) { merge(i, i+1); }
  puts("YES");
  dfs(fa_id - 1);
}
