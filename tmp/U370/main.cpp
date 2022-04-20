#include <bits/stdc++.h>

int main()
{
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  std::vector<bool> vis(n, false);

  int64_t ans = 0;

  for (int i = 0; i < 20; i++)
    if (std::all_of(a.begin(), a.end(), [i](int x) { return x & (1 << i); }))
    {
      ans += (1ll << i) * n;
      for (int j = 0; j < n; j++)
        a[j] ^= (1 << i);
    }

  std::vector<bool> valid(1 << 18, false);
  for (int i = 0; i < n; i++)
    valid[((1 << 18) - 1) ^ a[i]] = true;
  for (int i = 0; i < 18; i++)
    for (int j = 0; j < (1 << 18); j++)
      valid[j] = valid[j] | valid[j | (1 << i)];

  std::vector<int> dp(1 << 18, 0x3f3f3f3f);
  for (int i = 0; i < n; i++)
    dp[a[i]] = a[i];
  for (int i = (1 << 18) - 1; i > 0; i--)
    for (int j = i; j > 0; j = (j - 1) & i)
      if (valid[j])
        dp[i ^ j] = std::min(dp[i ^ j], dp[i] + (i ^ j));

  std::cout << ans + dp[0] << std::endl;

  return 0;
}
