#include <bits/stdc++.h>

#define rep(i,n) for (int i=0;i<n;++i)
#define repa(i,n) for (int i=1;i<=n;++i)

constexpr int N = 100005;
int x[N], n;

std::map<int, int> ans;
std::map<int, std::array<int, 2>> e;

void dfs(int u, int c) {
  ans[u] = c;
  for (int v: e[u]) if (ans[v] != c) {
    dfs(v, c); } }

int main() {
  int a, b;
  scanf("%d%d%d", &n, &a, &b);
  rep (i,n) scanf("%d", &x[i]);
  
  rep (i,n) { ans[x[i]] = -1; }
  rep (i,n) {
    e[x[i]] = {-1, -1};
    if (ans.count(a - x[i])) { e[x[i]][0] = a - x[i]; }
    if (ans.count(b - x[i])) { e[x[i]][1] = b - x[i]; }
    if (e[x[i]] == std::array<int,2>({-1, -1})) { puts("NO"); return 0; } }
  
  rep (i,n) {
    if (e[x[i]][0] == -1 || e[x[i]][1] == -1) {
      int should_ans = (e[x[i]][0] == -1);
      if (ans[x[i]] == !should_ans) { puts("NO"); return 0; }
      dfs(x[i], should_ans); } }

  puts("YES");
  rep (i,n) {
    if (ans[x[i]] == -1) { ans[x[i]] = 0; }
    printf("%d ", ans[x[i]]); }

  return 0;
}
