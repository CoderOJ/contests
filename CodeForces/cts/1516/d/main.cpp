#include <bits/stdc++.h>

constexpr int N = 100005;
constexpr int B = 20;

int a[N], n, m, q;
int r[N][B];
int rmost[N];

int main() {
  scanf ("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) scanf ("%d", &a[i]);

  m = *std::max_element (a, a + n);
  for (int i = 1; i <= m; ++i) rmost[i] = n;

  for (int i = 0; i <= n; ++i)
    for (int j = 0; j < B; ++j)
      r[i][j] = n;

  r[n][0] = n;
  for (int i = n - 1; i >= 0; i--) {
    r[i][0] = r[i + 1][0];
    if (a[i] != 1) {
      r[i][0] = std::min (r[i][0], rmost[a[i]]);
      rmost[a[i]] = i; }
    for (int j = 2; j * j <= a[i]; ++j) if (a[i] % j == 0) {
        r[i][0] = std::min (r[i][0], rmost[j]);
        r[i][0] = std::min (r[i][0], rmost[a[i] / j]);
        rmost[j] = i;
        rmost[a[i] / j] = i;
      }
  }

  for (int b = 0; b < B - 1; ++b) {
    for (int i = 0; i < n; ++i) {
      r[i][b + 1] = r[r[i][b]][b];
    }
  }

  while (q--) {
    int l, r;
    scanf ("%d%d", &l, &r);
    l--, r--;
    int pos = l, ans = 0;
    for (int i = B - 1; i >= 0; i--)
      if (::r[pos][i] <= r) {
        pos = ::r[pos][i];
        ans += (1 << i);
      }
    if (pos <= r) ans++;
    printf ("%d\n", ans);
  }
  return 0;
}
