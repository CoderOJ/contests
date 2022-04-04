#include <bits/stdc++.h>

const int N = 100005;
int a[N], n;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i <= n; i++) scanf("%d", &a[i]);
  std::reverse(a, a + n + 1);
  int last_p = 0;
  int64_t cur = a[last_p];
  int64_t ans = 1ll * a[0] * (4 * n + 1);
  for (int i = 1; i <= n; i++)
  {
    if (a[i] < a[last_p])
    {
      cur += 1ll * (i - last_p) * a[last_p];
      for (int j = last_p + 1; j <= i; j++) cur += a[j];
      last_p = i;
      ans = std::min<int64_t>(ans, cur * 2 + 1ll * ((n - i) * 4 - 1) * a[i]);
    }
  }
  std::cout << ans << std::endl;
  return 0;
}
