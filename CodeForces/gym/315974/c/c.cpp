#include <bits/stdc++.h>

#define rep(i,n) for (int i=0;i<n;++i)
#define repa(i,n) for (int i=1;i<=n;++i)

constexpr int N = 100005;
int x[N], n;

std::map<int, int> ans;
int prob[N];

int main() {
  int a, b;
  scanf("%d%d%d", &n, &a, &b);
  rep (i,n) scanf("%d", &x[i]);
  
  rep (i,n) ans[x[i]] = -1;

  rep (i,n) {
    prob[i] = ans.count(a - x[i]) + ans.count(b - x[i]);
    if (prob[i] == 0) { puts("NO"); return 0; } }

  rep (i,n) if (prob[i] == 1) {
    if (ans.count(a - x[i])) {
      if (ans[a - x[i]] == 1) {
        puts("NO"); return 0; }
      ans[a - x[i]] = ans[x[i]] = 0; }
    else {
      if (ans[b - x[i]] == 0) {
        puts("NO"); return 0; }
      ans[b - x[i]] = ans[x[i]] = 1; } }

  puts("YES");
  rep (i,n) {
    if (ans[x[i]] == -1) { ans[x[i]] = 0; }
    printf("%d ", ans[x[i]]); }

  return 0;
}
