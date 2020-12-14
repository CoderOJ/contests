#include <cstdio>
#include <cstring>
#include <iostream>
#define N 510
#define mod 998244353
using namespace std;
int n, k, l;
int f[N][10];
int
get(int s, int l)
{
  return (s >> l) & ((1 << k) - 1);
}
int
work(int s)
{
  for (int i = 0; i <= l - k; i++)
    if (((s >> get(s, i)) & 1) == 0)
      return 0;
  int m = (1 << (k - 1)) - 1;
  memset(f, 0, sizeof(f));
  f[l][s >> (l - k + 1)] = 1;
  for (int i = l + 1; i <= n; i++) {
    for (int j = 0; j < (1 << (k - 1)); j++)
      if (f[i - 1][j])
        for (int p = 0; p <= 1; p++) {
          int t = j | (p << (k - 1));
          if (((s >> t) & 1) == 0)
            continue;
          f[i][t & m] = (f[i][t & m] + f[i - 1][j]) % mod;
        }
  }
  int ans = 0;
  for (int i = 0; i <= m; i++)
    ans = (ans + f[n][i]) % mod;
  return ans;
}
int
main()
{
  scanf("%d%d", &n, &k);
  l = 1 << k;
  int ans = 0;
  for (int s = 0; s < 1 << l; s++)
    ans = (ans + work(s)) % mod;
  printf("%d\n", ans);
  return 0;
}
