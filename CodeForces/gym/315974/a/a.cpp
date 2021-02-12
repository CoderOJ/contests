#include <bits/stdc++.h>

#define rep(i,n) for (int i=0;i<n;++i)
#define repa(i,n) for (int i=1;i<=n;++i)

int main() {
  int n, k; scanf("%d%d", &n, &k);
  int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
  if (n == 4) { puts("-1"); return 0; }
  if (k <= n) { puts("-1"); return 0; }
  std::vector<int> other_nodes;
  repa (i,n) if (i != a && i != b && i != c && i != d) {
    other_nodes.push_back(i); }

  printf("%d %d ", a, c);
  for (int u: other_nodes) printf("%d ", u);
  printf("%d %d ", d, b);

  puts("");

  printf("%d %d ", c, a);
  for (int u: other_nodes) printf("%d ", u);
  printf("%d %d ", b, d);

  return 0;
}
