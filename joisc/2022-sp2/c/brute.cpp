#include <bits/stdc++.h>

#define rep(i,n) for (int i = 0; i < n; i++)

const int N = 10005;

int a[N], b[N], c[N];
int n;

int main()
{
  scanf("%d", &n);
  rep (i, n) scanf("%d%d%d", &a[i], &b[i], &c[i]);
  int ans = -1;
  rep (i, n) rep (j, n) rep (k, n)
    if (a[i] > a[j] && a[i] > a[k])
      if (b[j] > b[i] && b[j] > b[k])
        if (c[k] > c[i] && c[k] > c[j])
          ans = std::max(ans, a[i] + b[j] + c[k]);
  std::cout << ans << std::endl;
  return 0;
}
